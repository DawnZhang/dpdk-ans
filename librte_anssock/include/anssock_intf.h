/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2015-2017 Ansyun <anssupport@163.com>. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Ansyun <anssupport@163.com> nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ANSSOCK_INTF_H__
#define __ANSSOCK_INTF_H__

/**
 * @file
 *
 * ANS socket API defines.
 *
 * Note: 
 * 1. After fork(), children process can't copy parent's ans socket, so children proces shall not handle any parent's ans socket.
 * 2. Anssock API parameters are same as BSD socket.
 *
 */


/**
 *  Init ans socket lib. Each thread shall call it if the thread need invoke anssock API.
 *
 * @param  file_prefix 
 *  Prefix for hugepage filenames, shall be same as ANS startup parameter(--file-prefix).
 *  If input is NULL, the default file-prefix is "rte"
 * @return  
 *
 */
int anssock_init(char *file_prefix);

/**
 *  Creates  an endpoint for communication and returns a descriptor.
 *
 * @param domain      
 *
 * @param type
 *
 * @param protocol
 *  
 * @return  
 * On success, a file descriptor for the new socket is returned.  On error, -1 is returned, and errno is set appropriately.
 */
int anssock_socket(int domain, int type, int protocol);

/**
 * Binds a local IP address.
 *
 * @param sockfd
 *
 * @param addr
 *
 * @param addrlen
 *
 * @return  
 * On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
 */
int anssock_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
 * Connect to remote IP address. This is nonblocking function, so shall check EINPROGRESS.
 *
 * EINPROGRESS
 *             The  socket  is  nonblocking  and  the  connection  cannot  be  completed immediately.  It is possible to
 *             use epoll to check whether connect() completed successfully (EPOLLOUT event) or unsuccessfully (EPOLLERR event)
 *   
 * @param sockfd      
 *
 * @param addr
 *
 * @param addrlen
 *
 * @return  
 * If the connection or binding succeeds, zero is returned.  On error, -1 is returned, and errno is set appropriately.
 */
 int anssock_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
 *  sendto user data via socket. This is nonblocking function, so shall check EAGAIN.
 *
 * @param sockfd    
 * @param buf
 * @param len    
 * @param flags: don't support MSG_OOB
 * @param dest_addr    
 * @param addrlen
 *
 * @return  
 *   On success, these calls return the number of characters sent.  On error, -1 is returned, and errno is set appropriately.
 *   If errno is EAGAIN, no buffer for sending data.
 */
ssize_t anssock_sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);


/**
 *  Send user data via socket. This is nonblocking function, so shall check EAGAIN.
 *
 * @param sockfd       
 * @param buf
 * @param len       
 * @param flags: don't support MSG_OOB
 *
 * @return  
 *  On success, these calls return the number of characters sent.  On error, -1 is returned, and errno is set appropriately.
 *   If errno is EAGAIN, no buffer for sending data.
 */
ssize_t anssock_send(int sockfd, const void *buf, size_t len, int flags);

/**
 *  Write user data via socket. This is nonblocking function, so shall check EAGAIN.
 *
 * @param fd      
 * @param buf
 * @param count
 *
 * @return  
 *  On success, these calls return the number of characters sent.  On error, -1 is returned, and errno is set appropriately.
 *   If errno is EAGAIN, no buffer for sending data.
 */
ssize_t anssock_write(int fd, const void *buf, size_t count);

/**
 *  Writes iovcnt buffers of data described by iov to the file associated with the file descriptor fd ("gather output").
 *  Write user data via socket. This is nonblocking function, so shall check EAGAIN.
 *
 * @param fd      
 * @param iov
 * @param iovcnt
 *
 * @return  
 *  On success, these calls return the number of characters sent.  On error, -1 is returned, and errno is set appropriately.
 *   If errno is EAGAIN, no buffer for sending data.
 */
ssize_t anssock_writev(int fd, const struct iovec *iov, int iovcnt);

/**
 * Receive user data from socket. This function is designed as nonblocking function, so shall not set socket as nonblocking and work with epoll.
 *
 * @param sockfd      
 * @param buf
 * @param len       
 * @param flags: only support MSG_PEEK
 * @param src_addr       
 * @param addrlen
 *
 * @return  
 *  These calls return the number of bytes received, or -1 if an error occurred.  In the event of an error, errno is set to indicate the error.  
 *  If errno is EAGAIN, no data are present to be received.
 */      
ssize_t anssock_recvfrom(int sockfd, void *buf, size_t len, int flags,
                struct sockaddr *src_addr, socklen_t *addrlen);


/**
 * Receive user data from socket. This function is designed as nonblocking function, so shall not set socket as nonblocking.
 *
 * @param sockfd      
 * @param buf
 * @param len      
 * @param flags: only support MSG_PEEK
 *   
 * @return  
 *  These calls return the number of bytes received, or -1 if an error occurred.  In the event of an error, errno is set to indicate the error.  
 *  If errno is EAGAIN, no data are present to be received.
 */ 
ssize_t anssock_recv(int sockfd, void *buf, size_t len, int flags);


/**
 * Read user data from socket. This function is designed as nonblocking function, so shall not set socket as nonblocking.
 *
 * @param fd      
 * @param buf
 * @param count
 *
 * @return  
 *  These calls return the number of bytes received, or -1 if an error occurred.  In the event of an error, errno is set to indicate the error.  
 *  If errno is EAGAIN, no data are present to be received.
 */ 
ssize_t anssock_read(int fd, void *buf, size_t count);


/**
 * Reads iovcnt buffers from the file associated with the file descriptor fd into the buffers described by iov ("scatter input").
 *
 * @param fd      
 * @param iov
 * @param iovcnt
 *
 * @return  
 *  These calls return the number of bytes received, or -1 if an error occurred.  In the event of an error, errno is set to indicate the error.  
 *  If errno is EAGAIN, no data are present to be received.
 */ 
ssize_t anssock_readv(int fd, const struct iovec *iov, int iovcnt);

/**
 * Listen for connections on a socket
 *
 * @param  sockfd     
 * @param  backlog 
 * The  backlog  argument defines the maximum length to which the queue of pending connection. default value is 2048
 * @return  
 * On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
 */
int anssock_listen(int sockfd, int backlog);

/**
 * Accept a new socket. This function is designed as nonblocking function, so shall not set socket as nonblocking and work with epoll.
 *
 * @param sockfd      
 * @param addr 
 * @param addrlen 
 *
 * @return  
 * On success, these system calls return a nonnegative integer that is a descriptor for the accepted socket.  On error, -1 is returned, and errno is set appropriately.
 * If errno is EAGAIN, no connections are present to be accepted.
 */
int anssock_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/**
 * Close a socket.
 *
 * @param fd      
 *
 * @return  
 * Returns zero on success.  On error, -1 is returned, and errno is set appropriately.
 */
int anssock_close(int fd);

/**
 * Shutdown a socket.
 *
 * @param sockfd      
 * @param how 
 *   SHUT_RD,  SHUT_WR,  SHUT_RDWR  have  the  value  0,  1,  2, respectively
 *
 * @return  
 * Returns zero on success.  On error, -1 is returned, and errno is set appropriately.
 */
int anssock_shutdown(int sockfd, int how);


/**
 * Create a epoll socket.
 *
 * @param size      
 *
 * @return  
 *
 */
 int anssock_epoll_create(int size);

/**
 * Update epoll socket event.
 *
 * @param epfd     
 * @param op
 * @param fd     
 * @param event
 *
 * @return  
 *
 */
 int anssock_epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

/**
 * Waiting epoll socket event. Only support Edge Triggered.
 *
 * @param epfd
 * @param events
 * @param maxevents
 * max events shall less than 2048
 * @param timeout
 * The timeout argument specifies the minimum number of milliseconds that anssock_epoll_wait() will block. Specifying a timeout of -1 causes epoll_wait() to block indefinitely, 
 * while specifying a timeout equal to zero cause epoll_wait() to return immediately, even if no events are available.
 *
 * @return  
 * When successful, anssock_epoll_wait() returns the number of file descriptors ready for read, or zero if no file descriptor became ready during the requested timeout milliseconds.   
 * When  an  error  occurs,  anssock_epoll_wait() returns -1 and errno is set appropriately. *
 */
 int anssock_epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

/**
 * 
 * @param sockfd      
 * @param level: 
 *   only support SOL_SOCKET, IPPROTO_TCP       
 * @param optname: 
 *   only support SO_REUSEPORT, SO_KEEPALIVE, TCP_NODELAY, TCP_KEEPIDLE, TCP_KEEPINTVL, TCP_KEEPCNT
 * @param optval
 * @param optlen      
 *
 * @return  
 * On  success,  zero is returned.  On error, -1 is returned, and errno is set appropriately.
 */
int anssock_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

/**
 *  Returns  the address of the peer connected to the socket sockfd.
 *
 * @param sockfd       
 * @param addr
 * @param addrlen
 *
 * @return  
 * On  success,  zero is returned.  On error, -1 is returned, and errno is set appropriately.
 */
int anssock_getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);


/**
 * Returns the current address to which the socket sockfd is bound.
 *
 * @param sockfd      
 * @param addr
 * @param addrlen
 *
 * @return  
 * On  success,  zero is returned.  On error, -1 is returned, and errno is set appropriately.
 */
 int anssock_getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/**
 * Enable anssock API debug log
 *
 * @param flag  
 * 1: enable debug log, 0: disable log
 * @return  
 * 
 */
 void anssock_enable_log(int flag);

#endif /* __ANSSOCK_INTF_H__ */
