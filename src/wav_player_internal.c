/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#define LOG_TAG "CAPI_MEDIA_WAV_PLAYER"

#include <mm_sound.h>
#include <mm_sound_private.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <dlog.h>
#include "wav_player.h"
#include "wav_player_internal.h"
#include "wav_player_private.h"
#include <stdlib.h>

int wav_player_start_loop (const char *path, sound_type_e type, wav_player_playback_completed_cb cb, void *user_data, int loop_count, int * id)
{
	int ret = MM_ERROR_NONE;
	return __convert_wav_player_error_code(__func__, ret);
}

int wav_player_start_solo(const char *path, sound_type_e type, bool force_to_route_spk, wav_player_playback_completed_cb cb, void *user_data, int * id)
{
	int ret = MM_ERROR_NONE;
	return __convert_wav_player_error_code(__func__, ret);
}

int wav_player_start_solo_loop(const char *path, sound_type_e type, wav_player_playback_completed_cb cb, void *user_data, int loop_count, int * id)
{
	int ret = MM_ERROR_NONE;
	return __convert_wav_player_error_code(__func__, ret);
}
