
#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
    char *data;
    size_t length;
    
    void allocate_and_copy(const char *src, size_t len) {
        if (len == 0) {
            data = nullptr;
            length = 0;
            return;
        }
        data = new char[len + 1];
        std::memcpy(data, src, len);
        data[len] = '\0';
        length = len;
    }
    
    void cleanup() {
        if (data) {
            delete[] data;
            data = nullptr;
        }
        length = 0;
    }

public:
    str() : data(nullptr), length(0) {}
    
    str(const char &c) {
        allocate_and_copy(&c, 1);
    }
    
    str(const char *&& s_) {
        if (s_) {
            size_t len = std::strlen(s_);
            allocate_and_copy(s_, len);
        } else {
            data = nullptr;
            length = 0;
        }
    }
    
    str &operator=(const char *&& s_) {
        cleanup();
        if (s_) {
            size_t len = std::strlen(s_);
            allocate_and_copy(s_, len);
        }
        return *this;
    }
    
    str(const str &other) {
        if (other.data) {
            allocate_and_copy(other.data, other.length);
        } else {
            data = nullptr;
            length = 0;
        }
    }
    
    str &operator=(const str &other) {
        if (this != &other) {
            cleanup();
            if (other.data) {
                allocate_and_copy(other.data, other.length);
            }
        }
        return *this;
    }
    
    char &operator[](size_t pos) {
        return data[pos];
    }
    
    size_t len() const {
        return length;
    }
    
    str join(const std::vector<str> &strs) const {
        if (strs.empty()) {
            return str();
        }
        
        size_t total_length = 0;
        for (size_t i = 0; i < strs.size(); ++i) {
            total_length += strs[i].len();
        }
        
        total_length += (strs.size() - 1) * length;
        
        char *result = new char[total_length + 1];
        size_t pos = 0;
        
        for (size_t i = 0; i < strs.size(); ++i) {
            if (strs[i].data) {
                std::memcpy(result + pos, strs[i].data, strs[i].len());
                pos += strs[i].len();
            }
            
            if (i < strs.size() - 1 && data) {
                std::memcpy(result + pos, data, length);
                pos += length;
            }
        }
        
        result[total_length] = '\0';
        
        str result_str;
        result_str.data = result;
        result_str.length = total_length;
        
        return result_str;
    }
    
    str slice(size_t l, size_t r) const {
        if (l >= r || l >= length) {
            return str();
        }
        
        if (r > length) {
            r = length;
        }
        
        size_t slice_len = r - l;
        str result;
        if (data && slice_len > 0) {
            result.data = new char[slice_len + 1];
            std::memcpy(result.data, data + l, slice_len);
            result.data[slice_len] = '\0';
            result.length = slice_len;
        }
        
        return result;
    }
    
    ~str() {
        cleanup();
    }
};
