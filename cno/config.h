#pragma once

#ifndef CNO_BUFFER_ALLOC_MIN
/* The minimum size (in bytes) in which dynamically allocated buffers grow.
   Controls the number of heap allocations & amount of wasted heap space. */
#define CNO_BUFFER_ALLOC_MIN 256
#endif

#ifndef CNO_BUFFER_ALLOC_MIN_EXP
/* The minimum factor by which dynamically allocated buffers grow. */
#define CNO_BUFFER_ALLOC_MIN_EXP 1.5
#endif

#ifndef CNO_MAX_HTTP1_HEADER_SIZE
/* Max. length of an outbound header in HTTP/1.1 mode. If a header longer than this is
   passed to `cno_write_message`, it will return an assertion error. Does not affect
   inbound messages and HTTP 2. Controls stack space usage. */
#define CNO_MAX_HTTP1_HEADER_SIZE 2048
#endif

#ifndef CNO_MAX_HEADERS
/* Max. number of entries in the header table of inbound messages. Applies to both HTTP 1
   and HTTP 2. Does not affect outbound messages. Controls stack space usage. */
#define CNO_MAX_HEADERS 64
#endif

#ifndef CNO_MAX_CONTINUATIONS
/* Maximum number of CONTINUATION frames that can follow HEADERS/PUSH_PROMISE.
   We can't start processing these frames until we've concatenated them all into
   a single buffer. Controls peak memory consumption. */
#define CNO_MAX_CONTINUATIONS 3
#endif

#ifndef CNO_STREAM_BUCKETS
/* Number of buckets in the "stream id -> stream object" hash map. Must be prime to
   ensure an even distribution. Controls stack/heap usage, depending on where connection
   objects are allocated. */
#define CNO_STREAM_BUCKETS 61
#endif

#ifndef CNO_STREAM_RESET_HISTORY
/* Remember the last N streams for which RST_STREAM was sent. Frames on these streams
   will be ignored under the assumption that the other side has not seen the reset yet.
   If 0, all closed streams are assumed to be possibly-reset. */
#define CNO_STREAM_RESET_HISTORY 7
#endif
