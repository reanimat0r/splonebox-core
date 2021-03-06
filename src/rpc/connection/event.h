/**
 *    Copyright (C) 2015 splone UG
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    This file incorporates code covered by the following terms:
 *
 *    Copyright Neovim contributors. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <stdbool.h>     // for bool
#include "rpc/connection/event-defs.h"


typedef struct multiqueue multiqueue;
typedef void (*put_callback)(multiqueue *multiq, void *data);

multiqueue *multiqueue_new_parent(put_callback put_cb, void *data);
multiqueue *multiqueue_new_child(multiqueue *parent);
void multiqueue_free(multiqueue *this);
event multiqueue_get(multiqueue *this);
void multiqueue_put_event(multiqueue *this, event e);
void multiqueue_process_events(multiqueue *this);
bool multiqueue_empty(multiqueue *this);
void multiqueue_replace_parent(multiqueue *this, multiqueue *new_parent);

#define multiqueue_put(q, h, ...) \
  multiqueue_put_event(q, event_create(1, h, __VA_ARGS__));
