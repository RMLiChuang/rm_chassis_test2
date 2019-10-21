#include "Chassis_Task.h"
#include "bsp_can.h"
#include "robomaster_vcan.h"

extern moto_info_t motor_info[MOTOR_MAX_NUM];
pid_struct_t motor_pid[7];
float target_speed=1000;

void Chassis_Task(void const * argument)
{
  /* USER CODE BEGIN Chassis_Task */
	printf ("In Chassis_Task!\r\n");

  /* Infinite loop */
  for(;;)
  {
		for (uint8_t i = 0; i < 7; i++)
			{
				motor_info[i].rotor_speed_set = pid_calc(&motor_pid[i], 4000, motor_info[i].rotor_speed );
			}
	
		printf("In Chassis_Task's loop\r\n");
		set_motor_voltage(0, 													//设置电机速度
												motor_info[0].rotor_speed, 
												motor_info[1].rotor_speed, 
												motor_info[2].rotor_speed, 
												motor_info[3].rotor_speed_set);
		
		wave_form_data[0] = (short)motor_info[0].rotor_speed;
    wave_form_data[1] = (short)motor_info[1].rotor_speed;
		wave_form_data[2] = (short)motor_info[2].rotor_speed;
		wave_form_data[3] = (short)motor_info[3].rotor_speed_set;
		shanwai_send_wave_form();
    osDelay(10);
  }
  /* USER CODE END Chassis_Task */
}
