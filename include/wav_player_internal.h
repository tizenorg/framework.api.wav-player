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

#ifndef __TIZEN_MEDIA_WAV_PLAYER_INTERNAL_H__
#define __TIZEN_MEDIA_WAV_PLAYER_INTERNAL_H__

#include <tizen.h>
#include <sound_manager.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * @file wav_player_internal.h
 * @brief This file contains the WAV player API.
 */

/**
 * @brief Plays a WAV file.
 * @param[in] path	The WAV file path to play
 * @param[in] type	The sound type
 * @param[in] callback	The callback function to invoke when a WAV file is finished playing
 * @param[in] user_data	The user data to be passed to the callback function
 * @param[in] loop_count The number of loops for playing (-1 for infinite playing)
 * @param[out] id	The WAV player ID ( can be set to NULL )
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #WAV_PLAYER_ERROR_NONE Successful
 * @retval #WAV_PLAYER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #WAV_PLAYER_ERROR_INVALID_OPERATION Invalid operation
 *
 * @post	It invokes wav_player_playback_completed_cb() when a WAV file has finished playing.
 * @see wav_player_stop()
 * @see wav_player_playback_completed_cb()
 */
int wav_player_start_loop (const char *path, sound_type_e type, wav_player_playback_completed_cb cb, void *user_data, int loop_count, int * id);

/**
 * @brief Plays a WAV file (with no session, other streams will be muted).
 * @param[in] path	The WAV file path to play
 * @param[in] type	The sound type
 * @param[in] force_to_route_spk	Route output path to speaker
 * @param[in] callback	The callback function to invoke when a WAV file is finished playing
 * @param[in] user_data	The user data to be passed to the callback function
 * @param[out] id	The WAV player ID ( can be set to NULL )
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #WAV_PLAYER_ERROR_NONE Successful
 * @retval #WAV_PLAYER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #WAV_PLAYER_ERROR_INVALID_OPERATION Invalid operation
 *
 * @post	It invokes wav_player_playback_completed_cb() when a WAV file has finished playing.
 * @see wav_player_stop()
 * @see wav_player_playback_completed_cb()
 */
int wav_player_start_solo(const char *path, sound_type_e type, bool force_to_route_spk, wav_player_playback_completed_cb cb, void *user_data, int * id);

/**
 * @brief Plays a WAV file (with no session, other streams will be muted).
 * @param[in] path	The WAV file path to play
 * @param[in] type	The sound type
 * @param[in] callback	The callback function to invoke when a WAV file is finished playing
 * @param[in] user_data	The user data to be passed to the callback function
 * @param[in] loop_count The number of loops for playing (-1 for infinite playing)
 * @param[out] id	The WAV player ID ( can be set to NULL )
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #WAV_PLAYER_ERROR_NONE Successful
 * @retval #WAV_PLAYER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #WAV_PLAYER_ERROR_INVALID_OPERATION Invalid operation
 *
 * @post	It invokes wav_player_playback_completed_cb() when a WAV file has finished playing.
 * @see wav_player_stop()
 * @see wav_player_playback_completed_cb()
 */
int wav_player_start_solo_loop(const char *path, sound_type_e type, wav_player_playback_completed_cb cb, void *user_data, int loop_count, int * id);

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_MEDIA_WAV_PLAYER_INTERNAL_H__ */
