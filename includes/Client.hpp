#pragma once
#include <string>
#include <sys/types.h>
class Client{
    private:
        int _fd;
        int _port;
        size_t _maxBodySize;
        std::string _readRequest;
        std::string _writeRequest;
        size_t _serverIndex;    //new
    public:
        Client(int fd);
        Client(const Client &copy);
        Client &operator=(const Client &target);
        ~Client();

        int getFd()const;
        bool isRequestComplete()const;
        void setMaxBodySize(size_t size);
        void setWriteRequest(const std::string &response);
        void setServerIndex(size_t index);
        size_t getServerIndex() const;
        const std::string &getWriteRequest()const;
        void clearWriteRequest();
        bool appendreadRequest(const char *buff, ssize_t bytes);
        const std::string &getReadRequest() const;
};