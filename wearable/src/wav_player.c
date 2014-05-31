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
#include <wav_player.h>
#include <stdlib.h>


typedef struct _cb_data_{
	wav_player_playback_completed_cb cb;
	void * user_data;
} _cb_data;



static int __convert_wav_player_error_code(const char *func, int code)
{
	int ret = WAV_PLAYER_ERROR_INVALID_OPERATION;
	char *errorstr = NULL;
	switch(code)
	{
		case MM_ERROR_NONE:
			ret = WAV_PLAYER_ERROR_NONE;
			errorstr = "ERROR_NONE";
			break;
		case MM_ERROR_INVALID_ARGUMENT: 
		case MM_ERROR_SOUND_INVALID_POINTER:
		case WAV_PLAYER_ERROR_INVALID_PARAMETER:			
			ret = WAV_PLAYER_ERROR_INVALID_PARAMETER;
			errorstr = "INVALID_PARAMETER";			
			break;
		case MM_ERROR_SOUND_INTERNAL:
			ret = WAV_PLAYER_ERROR_INVALID_OPERATION;
			errorstr = "INVALID_OPERATION";			
			break;
		case MM_ERROR_SOUND_UNSUPPORTED_MEDIA_TYPE:
			ret = WAV_PLAYER_ERROR_FORMAT_NOT_SUPPORTED;
			errorstr = "FORMAT_NOT_SUPPORTED";
			break;
		default:
			ret = WAV_PLAYER_ERROR_INVALID_OPERATION;
			errorstr = "INVALID_OPERATION";
			
	}	
	LOGE( "[%s] %s(0x%08x)",func, errorstr, ret);
	return ret;
}


static void __internal_complete_cb(void *user_data, int id)
{
	_cb_data * cb_data = (_cb_data*)user_data;
	if(!cb_data)
		return;
	
	if( cb_data->cb ){
		LOGD( "user callback for handle %d call", id);
		cb_data->cb(id, cb_data->user_data);
	}
	free(cb_data);
}


int wav_player_start(const char *path, sound_type_e type, wav_player_playback_completed_cb cb, void *user_data,  int * id)
{
	int ret ;
	int player;
	char m_path[PATH_MAX];
	void (*_completed_cb)(void *, int);
	_completed_cb = NULL;
	_cb_data *cb_data = NULL;
	
	
	if( path == NULL)
		return __convert_wav_player_error_code(__func__, WAV_PLAYER_ERROR_INVALID_PARAMETER);

	if( type < SOUND_TYPE_SYSTEM || type > SOUND_TYPE_FIXED_CAMCORDING )
		return __convert_wav_player_error_code(__func__, WAV_PLAYER_ERROR_INVALID_PARAMETER);
	if (type >= SOUND_TYPE_FIXED ) {
		LOGW( "type is %d, we force to set SOUND_TYPE_FIXED", type);
		type = VOLUME_TYPE_FIXED;
	}

	m_path[0] = '\0';
	if( path[0] != '/' ){

		if( getcwd(m_path, PATH_MAX) != NULL){
			strncat(m_path, "/",PATH_MAX-strlen(m_path) );
		}
	}
	strncat(m_path, path, PATH_MAX-strlen(m_path));

	if( cb ){
		_completed_cb = __internal_complete_cb;
		cb_data = (_cb_data *)malloc(sizeof(_cb_data));
		if(cb_data == NULL )
			return __convert_wav_player_error_code(__func__, WAV_PLAYER_ERROR_INVALID_OPERATION);
		cb_data->cb = cb;
		cb_data->user_data = user_data;
	}

	
	ret = mm_sound_play_sound(m_path, type, _completed_cb , cb_data, &player);

	if( ret == 0 && id != NULL){
		*id = player;
	}
	
	if( ret != 0 && cb_data != NULL)
		free(cb_data);

	return __convert_wav_player_error_code(__func__, ret);
}

int wav_player_start_solo(const char *path, sound_type_e type, bool force_to_route_spk, wav_player_playback_completed_cb cb, void *user_data, int * id)
{
	int ret ;
	int player;
	char m_path[PATH_MAX];
	void (*_completed_cb)(void *, int);
	_completed_cb = NULL;
	_cb_data *cb_data = NULL;


	if( path == NULL) {
		return __convert_wav_player_error_code(__func__, WAV_PLAYER_ERROR_INVALID_PARAMETER);
	}

	if( type < SOUND_TYPE_SYSTEM || type > SOUND_TYPE_FIXED_CAMCORDING ) {
		return __convert_wav_player_error_code(__func__, WAV_PLAYER_ERROR_INVALID_PARAMETER);
	}

	m_path[0] = '\0';
	if( path[0] != '/' ){
		if( getcwd(m_path, PATH_MAX) != NULL){
			strncat(m_path, "/",PATH_MAX-strlen(m_path) );
		}
	}
	strncat(m_path, path, PATH_MAX-strlen(m_path));

	if( cb ){
		_completed_cb = __internal_complete_cb;
		cb_data = (_cb_data *)malloc(sizeof(_cb_data));
		if(cb_data == NULL )
			return __convert_wav_player_error_code(__func__, WAV_PLAYER_ERROR_INVALID_OPERATION);
		cb_data->cb = cb;
		cb_data->user_data = user_data;
	}

	if( type < SOUND_TYPE_FIXED ) {
		ret = mm_sound_play_solo_sound(m_path, type, _completed_cb , cb_data, &player);
	} else {
		int volume_config = VOLUME_TYPE_FIXED;
		switch (type) {
		case SOUND_TYPE_FIXED:
			volume_config |= VOLUME_GAIN_DEFAULT;
			break;
		case SOUND_TYPE_FIXED_AF:
			volume_config |= VOLUME_GAIN_AF;
			break;
		case SOUND_TYPE_FIXED_SHUTTER1:
			volume_config |= VOLUME_GAIN_SHUTTER1;
			break;
		case SOUND_TYPE_FIXED_SHUTTER2:
			volume_config |= VOLUME_GAIN_SHUTTER2;
			break;
		case SOUND_TYPE_FIXED_CAMCORDING:
			volume_config |= VOLUME_GAIN_CAMCORDING;
			break;
		default:
			break;
		}
		if (force_to_route_spk) {
			ret = mm_sound_play_loud_solo_sound(m_path, volume_config, _completed_cb , cb_data, &player);
		} else {
			ret = mm_sound_play_solo_sound(m_path, volume_config, _completed_cb , cb_data, &player);
		}
	}
	if( ret == 0 && id != NULL) {
		*id = player;
	}

	if( ret != 0 && cb_data != NULL) {
		free(cb_data);
	}

	return __convert_wav_player_error_code(__func__, ret);
}

int wav_player_stop(int id)
{
	return __convert_wav_player_error_code(__func__, mm_sound_stop_sound(id));
}

