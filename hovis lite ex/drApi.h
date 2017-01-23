#ifndef _DRAPI_H
#define _DRAPI_H

#ifdef __cplusplus
extern "C" {
#endif

// 이 클래스는 drApi.dll에서 내보낸 것입니다.
#include <windows.h>
#include <limits.h>

typedef enum EDrModule_t{
	_DR_MODULE_NONE					= 0,
	_DR_MODULE_MOTOR,
	_DR_MODULE_HEADLED,
	_DR_MODULE_CONTROLLER,
	_DR_MODULE_SENSOR,

	_DR_MODULE_MIN			= _DR_MODULE_MOTOR,
	_DR_MODULE_MAX			= _DR_MODULE_SENSOR,
} EDrModule_t;

typedef enum EDrResult_t
{
	_DR_SUCCESS									= 0,
	_DR_NULL_HANDLE,
	_DR_COM_OPEN_FAIL,
	_DR_NULL_DATA_ARG,
	_DR_WRONG_AXIS,

	_DR_SEND_INVALID_ARG_MODULE					= 10,
	_DR_SEND_INVALID_ARG_SIZE,
	_DR_SEND_INVALID_ARG_ID,
	_DR_SEND_INVALID_ARG_CMD,
	_DR_SEND_INVALID_ARG_DATA,
	_DR_SEND_FAIL,

	_DR_RECV_ERR_TIMEOUT						= 20,
	_DR_RECV_ERR_CHECKSUM,
	_DR_RECV_ERR_PACKET_SIZE_TOO_BIG,
	_DR_RECV_ERR_MOTOR_INVALID_CMD,
	_DR_RECV_ERR_MOTOR_INVALID_ID,
	_DR_RECV_ERR_MOTOR_INVALID_SIZE,
	_DR_RECV_ERR_MOTOR_INVALID_REG_RANGE,
	_DR_RECV_ERR_HEADLED_INVALID_CMD,
	_DR_RECV_ERR_HEADLED_INVALID_ID,
	_DR_RECV_ERR_HEADLED_INVALID_SIZE,
	_DR_RECV_ERR_HEADLED_INVALID_REG_RANGE,
	_DR_RECV_ERR_CONTROLLER_INVALID_CMD,
	_DR_RECV_ERR_CONTROLLER_INVALID_ID,
	_DR_RECV_ERR_CONTROLLER_INVALID_SIZE,
	_DR_RECV_ERR_CONTROLLER_INVALID_REG_RANGE,
	_DR_RECV_ERR_SENSOR_INVALID_CMD,
	_DR_RECV_ERR_SENSOR_INVALID_ID,
	_DR_RECV_ERR_SENSOR_INVALID_SIZE,
	_DR_RECV_ERR_SENSOR_INVALID_REG_RANGE,
} EDrResult_t;

// << Common >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
__declspec(dllimport) EDrResult_t	dr_common_initialize( HANDLE* hDr );
__declspec(dllimport) EDrResult_t	dr_common_destroy( HANDLE hDr );
__declspec(dllimport) EDrResult_t	dr_common_get_connection( HANDLE hDr, BOOL* pbConnection );
__declspec(dllimport) EDrResult_t	dr_common_connect( HANDLE hDr, const TCHAR* pszPort, DWORD dwBaudRate );
__declspec(dllimport) EDrResult_t	dr_common_disconnect( HANDLE hDr );
__declspec(dllimport) EDrResult_t	dr_common_send( HANDLE hDr, EDrModule_t ETargetModule, BYTE byPacketSize, BYTE byId, BYTE byCmd, BYTE* pbyData );
// << Controller >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
////////////////////////////////////////////////////////////////////////////////
// Controller
////////////////////////////////////////////////////////////////////////////////

typedef enum EDrControllerAxis_t
{
	_DR_CONTROLLER_AXIS_X,
	_DR_CONTROLLER_AXIS_Y,
	_DR_CONTROLLER_AXIS_Z,
	_DR_CONTROLLER_AXIS_ALL

} EDrControllerAxis_t;

__declspec(dllimport) EDrResult_t	dr_controller_receive_rom( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byLength );
__declspec(dllimport) EDrResult_t	dr_controller_get_rom( HANDLE hDr, BYTE byAddress, BYTE byLength, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_rom( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byLength, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byLength );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram( HANDLE hDr, BYTE byAddress, BYTE byLength, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byLength, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_connection_check( HANDLE hDr, BYTE byId, BYTE byLength, BYTE* pbyMotorId );
__declspec(dllimport) EDrResult_t	dr_controller_get_connection_check( HANDLE hDr, BYTE* pbyLength, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_play_motion( HANDLE hDr, BYTE byId, BYTE byMotion, BYTE byReady );
__declspec(dllimport) EDrResult_t	dr_controller_send_stop_motion( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_send_play_task( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_send_stop_task( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_receive_debug_task_start( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_receive_debug_task_step( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_debug_task_counter( HANDLE hDr, WORD* pwData );
__declspec(dllimport) EDrResult_t	dr_controller_send_play_ledbuzz( HANDLE hDr, BYTE byId, BYTE byLed, BYTE byBuzz );
__declspec(dllimport) EDrResult_t	dr_controller_receive_stat( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_stat( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_rollback( HANDLE hDr, BYTE byId, BYTE byIdSkip, BYTE byBaudSkip );
__declspec(dllimport) EDrResult_t	dr_controller_send_reboot( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_receive_zigbee( HANDLE hDr, BYTE byId, BYTE byInst );
__declspec(dllimport) EDrResult_t	dr_controller_get_zigbee( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_remocon( HANDLE hDr, BYTE byId, BYTE byChannel, BYTE byLength, BYTE byData );
__declspec(dllimport) EDrResult_t	dr_controller_send_fw_update( HANDLE hDr, BYTE byId );

__declspec(dllimport) EDrResult_t	dr_controller_receive_rom_version( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_rom_version( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_rom_id( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_rom_id( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_rom_id( HANDLE hDr, BYTE byId, BYTE byNewId );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_id( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_id( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_id( HANDLE hDr, BYTE byId, BYTE byNewId );
__declspec(dllimport) EDrResult_t	dr_controller_receive_rom_rmc_channel( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_rom_rmc_channel( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_rom_rmc_channel( HANDLE hDr, BYTE byId, BYTE byNewChannel );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_rmc_channel( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_rmc_channel( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_rmc_channel( HANDLE hDr, BYTE byId, BYTE byNewChannel );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_status( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_status( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_clear_ram_status( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_led_control( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_led_control( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_led_control( HANDLE hDr, BYTE byId, BYTE byNewControl );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_zigbee_channel( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_zigbee_channel( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_zigbee_channel( HANDLE hDr, BYTE byId, BYTE byNewChannel );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_zigbee_panid( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_zigbee_panid( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_zigbee_panid( HANDLE hDr, BYTE byId, WORD wNewPANID );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_zigbee_saddr( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_zigbee_saddr( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_zigbee_saddr( HANDLE hDr, BYTE byId, WORD wNewSADDR );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_zigbee_dstaddr( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_zigbee_dstaddr( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_zigbee_dstaddr( HANDLE hDr, BYTE byId, WORD wNewDSTADDR );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_zigbee_ackreq( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_zigbee_ackreq( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_zigbee_ackreq( HANDLE hDr, BYTE byId, BYTE byNewACKREQ );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_zigbee_backoff( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_zigbee_backoff( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_send_ram_zigbee_backoff( HANDLE hDr, BYTE byId, BYTE byNewBACKOFF );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_servo_count( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_servo_count( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_servo_id( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_servo_id( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_playing_motion( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_playing_motion( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_playing_task( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_playing_task( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_button_status( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_button_status( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_rmc_length( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_rmc_length( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_rmc_data( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_rmc_data( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_voltage( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_voltage( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_temperature( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_temperature( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_light_sensor( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_light_sensor( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_adc1_type( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_adc1_type( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_adc2_type( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_adc2_type( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_adc1_value( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_adc1_value( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_adc2_value( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_adc2_value( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_accgyro_connected( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_accgyro_connected( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_acc_value( HANDLE hDr, BYTE byId, EDrControllerAxis_t EDrAxis );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_acc_value( HANDLE hDr, BYTE* pbyData, EDrControllerAxis_t EDrAxis );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_gyro_value( HANDLE hDr, BYTE byId, EDrControllerAxis_t EDrAxis );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_gyro_value( HANDLE hDr, BYTE* pbyData, EDrControllerAxis_t EDrAxis );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_sound_detection( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_sound_detection( HANDLE hDr, BYTE* pbyData );
__declspec(dllimport) EDrResult_t	dr_controller_receive_ram_sound_direction( HANDLE hDr, BYTE byId );
__declspec(dllimport) EDrResult_t	dr_controller_get_ram_sound_direction( HANDLE hDr, BYTE* pbyData );

// << Timer >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
/* 주의 - 반드시 Init 을 해야 사용 가능하다 - */
////////////////////////////////////////////////////////////////////////////////
// Timer(Init, Destroy, Set, Get) - Init 을 해야 쓸 수 있는 함수들...
////////////////////////////////////////////////////////////////////////////////
__declspec(dllimport) char			dr_wait_timer_init(int nCnt);										// 내가 사용할 만큼(nCnt)의 타이머를 생성한다. (ex:nCnt = 3 -> 0 ~ 2 까지의 타이머 사용가능)
__declspec(dllimport) void			dr_wait_timer_destroy();											// 타이머 메모리 해제 - 이제부터 작동 안됨
__declspec(dllimport) void			dr_wait_timer_set(int nIndex);										// timer_get 과 쌍으로 set 한 시점에서 시간을 0 으로 본다.
__declspec(dllimport) unsigned long	dr_wait_timer_get(int nIndex);										// timer_set 한 후 얼마나 지났는가를 확인하는 타이머
__declspec(dllimport) char			dr_wait_timer_check(int nIndex, unsigned long t);					// timer_set 한 후 지정한 시간이 되면 true 를 반환, 단, 에러 발생시 혹은 시간이 안되면 false

/* Init 할 필요 없다. */
////////////////////////////////////////////////////////////////////////////////
// Time(년,월,일,시,분,초,현재시간 등
// 기준 시간은 1970년 1월 1일 0시 0분 0초 부터... (유닉스 타임)
////////////////////////////////////////////////////////////////////////////////
__declspec(dllimport) unsigned long	dr_wait_timer_curr();												// 현재의 시간을 ms 로 리턴하는 함수
__declspec(dllimport) int			dr_wait_timer_year();												// 컴퓨터의 year 값 리턴(4자리 ex:2012)
__declspec(dllimport) int			dr_wait_timer_month();												// 컴퓨터의 month 값 리턴
__declspec(dllimport) int			dr_wait_timer_day();												// 컴퓨터의 날짜 값 리턴
__declspec(dllimport) int			dr_wait_timer_week();												// 컴퓨터의 요일 값 리턴(일(0), 월(1), 화(2), 수(3), 목(4), 금(5), 토(6))
__declspec(dllimport) int			dr_wait_timer_hour();												// 컴퓨터의 시간 값 리턴
__declspec(dllimport) int			dr_wait_timer_minute();												// 컴퓨터의 minute 값 리턴
__declspec(dllimport) int			dr_wait_timer_second();												// 컴퓨터의 second 값 리턴
__declspec(dllimport) int			dr_wait_timer_millisecond();										// 컴퓨터의 millisecond 값 리턴

/* 주의 - dr_wait_break 를 사용 시 반드시 dr_wait_reset 을 해야만 다시 사용이 가능하다 - */
////////////////////////////////////////////////////////////////////////////////
// Delay
////////////////////////////////////////////////////////////////////////////////
__declspec(dllimport) void			dr_wait_delay_break();												// 모든 대기(wait - dr_wait_delay) 함수를 탈출하도록 한다.
__declspec(dllimport) void			dr_wait_delay_break_once();											// 동작하고 있는 대기(wait - dr_wait_delay) 함수를 한번 탈출하도록 한다.
__declspec(dllimport) void			dr_wait_delay_reset();												// break 명령으로 사용할 수 없게 된 delay 함수를 다시 사용 가능하게 해 준다.
__declspec(dllimport) void			dr_wait_delay(unsigned long);										// 지정한 시간(ms) 만큼 함수를 대기시킨다.

////////////////////////////////////////////////////////////////////////////////
// Wait Busy
////////////////////////////////////////////////////////////////////////////////
__declspec(dllimport) EDrResult_t	dr_wait_busy( HANDLE hDr, DWORD dwMilliSecond );

// << Motor >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> //
//////// Data ////////
////////////////////////////////////////////////////////////////////////////////
// 초기화 함수
////////////////////////////////////////////////////////////////////////////////
__declspec(dllimport) EDrResult_t dr_motor_init(HANDLE hDr);											// 모터 제어 전 반드시 한번 호출 하는 함수로 최초 한번만 실행해 주면 된다.
__declspec(dllimport) void dr_motor_destroy();															// 모터 제어를 종료할 때, 혹은 프로그램을 종료하기 전에 반드시 한번 호출 해 주어야 하는 함수
////////////////////////////////////////////////////////////////////////////////
// 파라미터 설정 함수
////////////////////////////////////////////////////////////////////////////////
// 실제 ID 에 가상의 AliasID 를 부여
__declspec(dllimport) void dr_motor_set_param_alias_id(int nID, int nAliasID);							// 특정 아이디에 AliasID 를 부여하는 함수
__declspec(dllimport) int dr_motor_get_param_alias_id_by_id(int nID);									// 해당 아이디에 셋 되어 있는 AliasID를 가져오는 함수
__declspec(dllimport) void dr_motor_set_param_dir(int nID, char cReverse);								// cReverse = 0(정방향), cReverse = 1(역방향)
__declspec(dllimport) char dr_motor_get_param_dir(int nID);												// return value = 0(정방향), return value = 1(역방향)
__declspec(dllimport) int dr_motor_get_param_id_by_alias_id(int nAliasID);								// AliasID 를 이용해서 실제 아이디 값을 가져오기

////////////////////////////////////////////////////////////////////////////////
// motor 구동 함수 모음(led(default-off), mode(default-위치제어), stop(default-false), evd/angle, 
// noaction(default-true) => 단, dr_motor_set_command_position/angle 의 위치제어함수를 사용시 자동으로 NoAction = false 가 되어 모터가 동작한다.(즉, 위치값을 넣는 순간 모터는 동작 가능상태가 된다.)
////////////////////////////////////////////////////////////////////////////////
// 구동시 초기화 함수
__declspec(dllimport) void dr_motor_set_command_init();													// 모터제어 명령 전에 반드시 호출해 주어야 하는 함수. 이 함수를 호출하면 변수전체가 리셋되고, Stop 명령의 플래그가 클리어 된다.
// Data
__declspec(dllimport) void dr_motor_set_command_position(int nID, int nPos);							// Evd 위치제어시 사용하는 함수
__declspec(dllimport) void dr_motor_set_command_angle(int nID, float fAngle);							// 각도를 이용한 위치제어시 사용하는 함수
__declspec(dllimport) int dr_motor_get_command_position(int nID);										// 현재 명령이 내려진 Evd 값을 읽어온다.
__declspec(dllimport) float dr_motor_get_command_angle(int nID);										// 현재 명령이 내려진 Angle 값을 읽어온다.
__declspec(dllimport) void dr_motor_set_command_flag(int nID, BOOL bStop, BOOL bMode_Speed, BOOL bLed_Green, BOOL bLed_Blue, BOOL bLed_Red, BOOL bNoAction); // flag 설정을 한번에 전부 할수 있는 명령(정지, 모드설정, LED, NoAction)
__declspec(dllimport) int dr_motor_get_command_flag(int nID);											// 현재 설정된 flag 설정을 한번에 가져오는 명령어
__declspec(dllimport) void dr_motor_set_command_flag_stop(int nID, BOOL bStop);							// flag 명령: 모터동작 지령전 이 함수를 set(bStop = true) 하면 모터의 지령이 "정지"로 변경된다.(단, m_bStop 내부변수가 셋되는 명령이 아니다. 정지도 하나의 제어로 생각하는 함수)
__declspec(dllimport) void dr_motor_set_command_flag_mode(int nID, BOOL bMode_Speed);					// flag 명령: 모터동작 지령전 이 함수를 call 하면 모터의 제어상태(0-위치, 1-속도)가 바뀐다.
__declspec(dllimport) void dr_motor_set_command_flag_led(int nID, BOOL bGreen, BOOL bBlue, BOOL bRed);	// flag 명령: 모터동작 지령전 이 함수를 call 하면 모터의 LED 상태를 변경할 수 있다.
__declspec(dllimport) void dr_motor_set_command_flag_led_green(int nID, BOOL bGreen);					// flag 명령: 모터동작 지령전 이 함수를 call 하면 모터의 LED 상태(녹색)를 변경할 수 있다.
__declspec(dllimport) void dr_motor_set_command_flag_led_blue(int nID, BOOL bBlue);						// flag 명령: 모터동작 지령전 이 함수를 call 하면 모터의 LED 상태(청색)를 변경할 수 있다.
__declspec(dllimport) void dr_motor_set_command_flag_led_red(int nID, BOOL bRed);						// flag 명령: 모터동작 지령전 이 함수를 call 하면 모터의 LED 상태(적색)를 변경할 수 있다.
__declspec(dllimport) void dr_motor_set_command_flag_noaction(int nID, BOOL bNoAction);					// flag 명령: 모터동작 지령전 이 함수를 set(bNoAction = true) 하면 모터가 동작하지 않는다.

__declspec(dllimport) BOOL dr_motor_get_command_flag_led_green(int nID);								// flag: 모터의 LED 지령상태(현재상태 아님) 중 녹색 설정 여부를 확인한다.
__declspec(dllimport) BOOL dr_motor_get_command_flag_led_blue(int nID);									// flag: 모터의 LED 지령상태(현재상태 아님) 중 청색 설정 여부를 확인한다.
__declspec(dllimport) BOOL dr_motor_get_command_flag_led_red(int nID);									// flag: 모터의 LED 지령상태(현재상태 아님) 중 적색 설정 여부를 확인한다.

__declspec(dllimport) void dr_motor_send_move(HANDLE hDr, int nTime);									// 실제 지령: 실제 모터의 지령, 기 설정된 명령데로 모터를 동작시키는 명령, nTime ms(1/1000s) 의 속도로 동작(모터 동작시)

/* 초기화 함수 이후 현 모터의 기본 설정으로 계산됨 */
////////////////////////////////////////////////////////////////////////////////
// 계산함수 모음
////////////////////////////////////////////////////////////////////////////////
///////// calc /////////////
__declspec(dllimport) int dr_motor_calc_angle2evd(int nID, float fValue);								// 해당 모터의 각도값을 Evd 값으로 변경해 주는 함수
__declspec(dllimport) float dr_motor_calc_evd2angle(int nID, int nValue);								// 해당 모터의 Evd 값을 각도값으로 변경해 주는 함수
__declspec(dllimport) int dr_motor_calc_time2tick(int nTime);											// 해당 모터의 시간값(ms)을 실제 모터에서 사용하는 Tick 값으로 변경하는 함수(1 Tick 당 11.2 ms)
////////////////////////////////////////////////////////////////////////////////
// 값 제한 함수 모음
////////////////////////////////////////////////////////////////////////////////
//////// Limit ////////
__declspec(dllimport) void dr_motor_set_limit_en(BOOL bOn);												// 이 함수의 bOn = off(Default On) 한 경우 모터의 limit 파라미터 설정을 무시한다. 즉, 리미트 없이 동작한다.(데드존 및 기구적 충돌 주의 필요)
__declspec(dllimport) BOOL dr_motor_get_limit_en();														// Limit 설정이 되어 있는지를 확인하는 함수
__declspec(dllimport) int Clip(int nLimitValue_Up, int nLimitValue_Dn, int nData);						// 내부적으로 사용하는 함수로 clipping 함수(정수)
__declspec(dllimport) float Clipf(float fLimitValue_Up, float fLimitValue_Dn, float fData);				// 내부적으로 사용하는 함수로 clipping 함수(실수)
__declspec(dllimport) int dr_motor_calc_limit_evd(int nID, int nValue);									// evd 를 limit 값을 넘지 않게 클리핑하는 함수로(파라미터 셋 필요-Init 함수 콜시 기본 설정이 된다.) nValue 에 값을 넣으면 결과값을 리턴받는다.
__declspec(dllimport) float dr_motor_calc_limit_angle(int nID, float fValue);							// 각도를 limit 값을 넘지 않게 클리핑하는 함수로(파라미터 셋 필요-Init 함수 콜시 기본 설정이 된다.) fValue 에 값을 넣으면 결과값을 리턴받는다.
/////////////////////

////////////////////////////////////////////////////////////////////////////////
// Stop & Ems & Reset
////////////////////////////////////////////////////////////////////////////////
__declspec(dllimport) BOOL dr_motor_get_status_stop();													// 정지 명령이 설정되어 있는지 확인(init 함수 call 시, 혹은 리셋관련함수 call 시 해제 됨)
__declspec(dllimport) BOOL dr_motor_get_status_Ems();													// 정지 명령이 설정되어 있는지 확인(리셋 시 해제 됨)

////////////////////////////////////////////////////////////////////////////////
// Reset 관련 함수
////////////////////////////////////////////////////////////////////////////////
__declspec(dllimport) void dr_motor_send_reset(HANDLE hDr, int nID);									// 모터에 reset 명령을 내리는 함수, stop/ems(비상정지) 도 초기화 된다.
__declspec(dllimport) void dr_motor_set_reset_stop();													// stop 플래그만 reset 하는 함수
__declspec(dllimport) void dr_motor_set_reset_ems();													// 비상정지 상태만 해제하는 함수, 이 함수를 call 하면 이후 모터 동작지령이 가능하다. 단, 사전에 에러요인을 없애는 것이 먼저 필요하다.(기구적 충돌 등)
__declspec(dllimport) void dr_motor_send_rollback(int nID, BOOL bIgnoreID, BOOL bIgnoreBaudrate);		// 모터에 공장초기화 명령을 내리는 함수, 이 함수를 call 하면 최초 판매상태로 모터가 변경이 된다.

////////////////////////////////////////////////////////////////////////////////
__declspec(dllimport) EDrResult_t dr_motor_receive_rom( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byLength );						// (rom)모터에 직접명령: 해당 모터(byID)의 byAddress 부터 byLength 만큼의 설정값을 가져오도록 지령하는 함수 
__declspec(dllimport) EDrResult_t dr_motor_get_rom( HANDLE hDr, BYTE byAddress, BYTE byLength, BYTE* pbyData );						// (rom)올라온 모터값을 확인하는 함수, byAddress 부터 byLength 만큼의 설정값을 pbyData 에 기록하여 준다.
__declspec(dllimport) EDrResult_t dr_motor_send_rom( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byLength, BYTE* pbyData );			// (rom)모터에 byAddress 부터 byLength 만큼의 설정값을 직접 써 넣어주는 함수
__declspec(dllimport) EDrResult_t dr_motor_receive_ram( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byLength );						// (ram)모터에 직접명령: 해당 모터(byID)의 byAddress 부터 byLength 만큼의 설정값을 가져오도록 지령하는 함수 
__declspec(dllimport) EDrResult_t dr_motor_get_ram( HANDLE hDr, BYTE byAddress, BYTE byLength, BYTE* pbyData );						// (ram)올라온 모터값을 확인하는 함수, byAddress 부터 byLength 만큼의 설정값을 pbyData 에 기록하여 준다.
__declspec(dllimport) EDrResult_t dr_motor_send_ram( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byLength, BYTE* pbyData );			// (ram)모터에 byAddress 부터 byLength 만큼의 설정값을 직접 써 넣어주는 함수
__declspec(dllimport) EDrResult_t dr_motor_send_command( HANDLE hDr, BYTE byId, BYTE byCommand );									// 모터에 직접 명령: command 명령 하나만 내릴 때 사용
__declspec(dllimport) EDrResult_t dr_motor_send_ram_one_data( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byData );					// 모터에 직접 명령: command, 하나의 data 명령을 내릴 때 사용
__declspec(dllimport) EDrResult_t dr_motor_send_ram_two_data( HANDLE hDr, BYTE byId, BYTE byAddress, BYTE byData0, BYTE byData1 );	// 모터에 직접 명령: command, 두개의 data 명령을 내릴 때 사용
__declspec(dllimport) EDrResult_t dr_motor_send_data( HANDLE hDr, BYTE byId, BYTE byCommand, BYTE byLength, BYTE* pbyData );		// 모터에 직접 명령: command, 여러개의 data 명령을 내릴 때 사용
__declspec(dllimport) EDrResult_t dr_motor_send_driver_servo_on_off(HANDLE hDr, int nID, BYTE byDriverOn, BYTE byServoOn);			// 모터에 직접 명령: Servo/Driver 의 On/Off 지령

#ifdef __cplusplus
}
#endif

#endif