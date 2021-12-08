#include "event.h"

#include "hmemory.h"
#include "containers/darry.h"
typedef struct registered_event{
    void* listener;
    PFN_on_event callback;
}registered_event;

typedef struct event_code_entry{
    registered_event* events;
} event_code_entry;

// This should be more than enough codes...
#define MAX_MESSAGE_CODES 16384

// State structure
typedef struct event_system_state{
    // Lookup table for event codes.
    event_code_entry registerd[MAX_MESSAGE_CODES];
} event_system_state;

/**
 * Event system internal state
 * 
 */
static b8 is_initialized = FALSE;
static event_system_state state;

b8 event_initialize(){
    if(is_initialized == TRUE){
        return FALSE;
    }
    is_initialized = FALSE;
    hzero_memory(&state, sizeof(state));

    is_initialized = TRUE;

    return TRUE;
}

void event_shutdown(){
    // Free the events arrays. And objects pointed to should be destroyed on their own.
    for(u64 i = 0; i < MAX_MESSAGE_CODES; ++i){
        if(state.registerd[i].events != 0){
            darray_destroy(state.registerd[i].events);
            state.registerd[i].events = 0;
        }
    }
}

b8 event_register(u16 code, void* listener, PFN_on_event on_event){
    if(is_initialized == FALSE){
        return FALSE;
    }

    if(state.registerd[code].events == 0){
        state.registerd[code].events = darray_create(registered_event);
    }

    u64 registerd_count = darray_length(state.registerd[code].events);
    for(u64 i = 0; i < registerd_count; ++i){
        if(state.registerd[code].events[i].listener == listener){
            // TODO: warn
            return FALSE;
        }
    }
         registered_event event;
        event.listener = listener;
        event.callback = on_event;
        darray_push(state.registerd[code].events, event);
        
        return TRUE;   
}

b8 event_unregister(u16 code, void* listener, PFN_on_event on_event){
    if(is_initialized == FALSE){
        return FALSE;
    }

    if(state.registerd[code].events == 0){
        // TODO: warn
        return FALSE;
    }
        u64 registed_count = darray_length(state.registerd[code].events);
        for(u64 i = 0; i < registed_count; ++i){
            registered_event e = state.registerd[code].events[i];
            if(e.listener == listener && e.callback == on_event){
                // Found one, remove it
                registered_event popped_event;
                darray_pop_at(state.registerd[code].events, i, &popped_event);
                return TRUE;
            }
        }
        // Not found
        return FALSE;   
}

b8 event_fire(u16 code, void* sender, event_context context){
    if(is_initialized == FALSE){
        return FALSE;
    }

    // If nothing is registerd for the code, boot out.
    if(state.registerd[code].events == 0){
        return FALSE;
    }

    u64 registed_count = darray_length(state.registerd[code].events);
        for(u64 i = 0; i < registed_count; ++i){
            registered_event e = state.registerd[code].events[i];
            if(e.callback(code, sender, e.listener, context)){
                return TRUE;
            }
        }
    return FALSE;
}