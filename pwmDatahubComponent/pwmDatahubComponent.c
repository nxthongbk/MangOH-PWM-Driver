#include "legato.h"
#include "interfaces.h"

#define PWM_DATAHUB	"pwmDatahubInput/input"

COMPONENT_INIT
{	
	le_result_t result;
	// This will be provided to the Data Hub.
	result = io_CreateInput(PWM_DATAHUB,
				IO_DATA_TYPE_JSON,
				"input");
	LE_ASSERT(result == LE_OK);

	result = admin_SetSource("/app/pwmControl/" PWM_DATAHUB,
				 "/app/pwmDatahub/" PWM_DATAHUB);
	LE_ASSERT(result == LE_OK);

	char json_str[IO_MAX_STRING_VALUE_LEN];
	for (int i = 1; i < 17; i++) {
		LE_INFO("Display interface number: %d", i);
		memset(json_str, 0 , IO_MAX_STRING_VALUE_LEN);
		for (int n = 0; n <= 180; n = n + 10) {
			sprintf(json_str,
				"{\"interface\":%d,\"angle\":%d}",
				i,
				n);
			io_PushJson(PWM_DATAHUB, IO_NOW, (const char *)json_str);
			sleep(1);
		}
		sleep(1);
	}
}