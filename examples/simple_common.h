#ifndef _SIMPLE_COMMON_H_
#define _SIMPLE_COMMON_H_
#include "cno.h"


void log_frame(int fd, cno_frame_t *frame, int recv)
{
    const char *e = recv ? "recv" : "sent";
    fprintf(stdout, "%d: %s frame %x (%s; length=%lu; flags=%x) on stream %lu\n", fd, e,
        frame->type, cno_frame_get_name(frame), frame->payload.size, frame->flags, frame->stream_id);
}


void log_message(int fd, cno_message_t *msg, int recv)
{
    const char *e = recv ? "recv" : "sent";
    fprintf(stdout, "%d: %s message HTTP/%d.%d %d, method = ", fd, e, msg->major, msg->minor, msg->code);
    fwrite(msg->method.data, msg->method.size, 1, stdout);
    fprintf(stdout, ", path = ");
    fwrite(msg->path.data, msg->path.size, 1, stdout);
    fprintf(stdout, ", headers:\n");

    size_t k = 0;

    for (; k < msg->headers_len; ++k) {
        fprintf(stdout, "    (%lu) ", msg->headers[k].name.size);
        fwrite(msg->headers[k].name.data, msg->headers[k].name.size, 1, stdout);
        fprintf(stdout, " = (%lu) ", msg->headers[k].value.size);
        fwrite(msg->headers[k].value.data, msg->headers[k].value.size, 1, stdout);
        fprintf(stdout, "\n");
    }
}


int log_recv_frame(cno_connection_t *conn, int *fd, cno_frame_t *frame)
{
    log_frame(*fd, frame, 1);
    return CNO_OK;
}


int log_sent_frame(cno_connection_t *conn, int *fd, cno_frame_t *frame)
{
    log_frame(*fd, frame, 0);
    return CNO_OK;
}


int write_to_fd(cno_connection_t *conn, int *fd, const char *data, size_t length)
{
    size_t wrote = 0;

    do {
        wrote += write(*fd, data + wrote, length - wrote);
    } while (wrote < length);

    return CNO_OK;
}


int log_recv_message(cno_connection_t *conn, int *fd, size_t stream, cno_message_t *msg)
{
    log_message(*fd, msg, 1);
    return CNO_OK;
}


int log_recv_message_data(cno_connection_t *conn, int *fd, size_t stream, const char *data, size_t length)
{
    if (length) {
        fprintf(stdout, "%d: recv data: ", *fd);
        fwrite(data, length, 1, stdout);

        if (data[length - 1] != '\n') {
            fprintf(stdout, "\n");
        }
    }
    return CNO_OK;
}


int log_recv_message_end(cno_connection_t *conn, int *fd, size_t stream, int disconnect)
{
    fprintf(stdout, "%d: recv end of message; stream %lu %s\n", *fd, stream, disconnect ? "closed" : "half-closed");
    return CNO_OK;
}

#endif
