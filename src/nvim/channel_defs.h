#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "nvim/eval/typval_defs.h"
#include "nvim/event/libuv_process.h"
#include "nvim/event/multiqueue.h"
#include "nvim/event/process.h"
#include "nvim/event/socket.h"
#include "nvim/event/stream.h"
#include "nvim/garray_defs.h"
#include "nvim/macros_defs.h"
#include "nvim/main.h"
#include "nvim/map_defs.h"
#include "nvim/msgpack_rpc/channel_defs.h"
#include "nvim/os/pty_process.h"
#include "nvim/terminal.h"
#include "nvim/types_defs.h"

#define CHAN_STDIO 1
#define CHAN_STDERR 2

typedef enum {
  kChannelStreamProc,
  kChannelStreamSocket,
  kChannelStreamStdio,
  kChannelStreamStderr,
  kChannelStreamInternal,
} ChannelStreamType;

typedef enum {
  kChannelPartStdin,
  kChannelPartStdout,
  kChannelPartStderr,
  kChannelPartRpc,
  kChannelPartAll,
} ChannelPart;

typedef enum {
  kChannelStdinPipe,
  kChannelStdinNull,
} ChannelStdinMode;

typedef struct {
  Stream in;
  Stream out;
} StdioPair;

typedef struct {
  bool closed;
} StderrState;

typedef struct {
  LuaRef cb;
  bool closed;
} InternalState;

typedef struct {
  Callback cb;
  dict_T *self;
  garray_T buffer;
  bool eof;
  bool buffered;
  bool fwd_err;
  const char *type;
} CallbackReader;

#define CALLBACK_READER_INIT ((CallbackReader){ .cb = CALLBACK_NONE, \
                                                .self = NULL, \
                                                .buffer = GA_EMPTY_INIT_VALUE, \
                                                .buffered = false, \
                                                .fwd_err = false, \
                                                .type = NULL })
