#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/io.h>
#include <stdio.h>
#include <errno.h>

#include "legato.h"
#include "interfaces.h"
#include "le_mutex.h"
#include "json.h"

#define PWM_DATAHUB	"pwmDatahubInput/input"

static void json_extract_dump(le_result_t res)
{
	if (res == LE_OK) {
		LE_INFO("json_Extract: successful");
	}
	if (res == LE_FORMAT_ERROR) {
		LE_ERROR("json_Extract: there's something wrong with the input JSON string.");
	}
	if (res == LE_BAD_PARAMETER) {
		LE_ERROR("json_Extract: there's something wrong with the extraction specification");
	}
	if (res == LE_NOT_FOUND) {
		LE_ERROR("json_Extract: the thing we are trying to extract doesn't exist in the JSON input");
	}
	if (res == LE_OVERFLOW) {
		LE_ERROR("json_Extract: the provided result buffer isn't big enough");
	}
}

static void pwmDataHubHandle(double timestamp,
			     const char* LE_NONNULL value,
			     void* contextPtr)
{
	char buffer[IO_MAX_STRING_VALUE_LEN];
	int interface;
	int angle;
	le_result_t le_res;
	json_DataType_t json_data_type;

	LE_INFO("pwmDataHubHandle: timestamp %lf", timestamp);
	LE_INFO("pwmDataHubHandle: value %s", value);

	if (!json_IsValid(value)) {
		LE_ERROR("INVALID JSON string");
		return;
	}
	 
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);

	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "interface", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for interface");
		return;
	}
	interface = (int)json_ConvertToNumber(buffer);

	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "angle", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for angle");
		return;
	}
	angle = (int)json_ConvertToNumber(buffer);
	
	ma_pwm_set_angle(interface,angle);
}
COMPONENT_INIT
{
	le_result_t result;
	ma_pwm_servo_init();
	// This will be received from the Data Hub.
	result = io_CreateOutput(PWM_DATAHUB,
				 IO_DATA_TYPE_JSON,
				 "input");
	LE_ASSERT(result == LE_OK);
	// Register for notification of updates to the counter value.
	io_AddJsonPushHandler(PWM_DATAHUB,
			      pwmDataHubHandle,
			      NULL);
}