#pragma once
#include "vulkan_types.inl"

/**
 * Returns the string rep of result.
 * @param resut The result to get the string for.
 * @param get_extended Indicates wether to also return an extended result.
 * @returns The error code and/or extended error message in string form. Defaults to success for unknown result types.
 */ 

const char* vulkan_result_string(VkResult result, b8 get_extended);
/**
 * @returns true if success, otherwise false. 
 */
b8 vulkan_result_is_success(VkResult result);