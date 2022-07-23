/**
 * @brief Get a unique ID for use in ImGui draw calls
 * 
 * @return size_t a unique ID
 */
size_t getNextID(){
    // While this can technically wrap, it's pretty much guaranteed to not happen for obvious practical reasons
    static size_t id;
    return id++;
}
