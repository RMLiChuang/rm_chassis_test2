#ifndef __Chassis_Task_H
#define __Chassis_Task_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
/********freertos��Ҫ���õĿ��ļ�********/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
/********�����������ļ�********/
#include "dji_remote.h"
//#include "oled.h"
//#include "oledfont.h"	
#include "pid.h"
#include "user_lib.h"
	 
extern moto_info_t motor_info[MOTOR_MAX_NUM];
extern pid_struct_t motor_pid[7];
/*****�����˶�״̬������״̬��ǩ*****/
typedef enum
{
  CHASSIS_VECTOR_FOLLOW_GIMBAL_YAW,
  CHASSIS_VECTOR_FOLLOW_CHASSIS_YAW,
  CHASSIS_VECTOR_NO_FOLLOW_YAW,
  CHASSIS_VECTOR_RAW,

  //  CHASSIS_AUTO,
  //  CHASSIS_FOLLOW_YAW,
  //  CHASSIS_ENCODER,
  //  CHASSIS_NO_ACTION,
  //  CHASSIS_RELAX,
} chassis_mode_e;

typedef struct
{
  const moto_info_t *chassis_motor_measure;
  fp32 accel;
  fp32 speed;
  fp32 speed_set;
  int16_t give_current;
} Chassis_Motor_t;


/*****�����˶�����������*****/
typedef struct
{
  const RC_Type *chassis_RC;               //����ʹ�õ�ң����ָ��
//  const Gimbal_Motor_t *chassis_yaw_motor;   //����ʹ�õ�yaw��̨�������ԽǶ���������̵�ŷ����
//  const Gimbal_Motor_t *chassis_pitch_motor; //����ʹ�õ�pitch��̨�������ԽǶ���������̵�ŷ����
//  const fp32 *chassis_INS_angle;             //��ȡ�����ǽ������ŷ����ָ��
  chassis_mode_e chassis_mode;               //���̿���״̬��
  chassis_mode_e last_chassis_mode;          //�����ϴο���״̬��
  Chassis_Motor_t motor_chassis[4];          //���̵������
  pid_struct_t motor_speed_pid[4];             //���̵���ٶ�pid
  pid_struct_t chassis_angle_pid;              //���̸���Ƕ�pid

  first_order_filter_type_t chassis_cmd_slow_set_vx;
  first_order_filter_type_t chassis_cmd_slow_set_vy;

  fp32 vx;                         //�����ٶ� ǰ������ ǰΪ������λ m/s
  fp32 vy;                         //�����ٶ� ���ҷ��� ��Ϊ��  ��λ m/s
  fp32 wz;                         //������ת���ٶȣ���ʱ��Ϊ�� ��λ rad/s
  fp32 vx_set;                     //�����趨�ٶ� ǰ������ ǰΪ������λ m/s
  fp32 vy_set;                     //�����趨�ٶ� ���ҷ��� ��Ϊ������λ m/s
  fp32 wz_set;                     //�����趨��ת���ٶȣ���ʱ��Ϊ�� ��λ rad/s
  fp32 chassis_relative_angle;     //��������̨����ԽǶȣ���λ rad/s
  fp32 chassis_relative_angle_set; //���������̨���ƽǶ�
  fp32 chassis_yaw_set;

  fp32 vx_max_speed;  //ǰ����������ٶ� ��λm/s
  fp32 vx_min_speed;  //ǰ��������С�ٶ� ��λm/s
  fp32 vy_max_speed;  //���ҷ�������ٶ� ��λm/s
  fp32 vy_min_speed;  //���ҷ�����С�ٶ� ��λm/s
  fp32 chassis_yaw;   //�����Ǻ���̨������ӵ�yaw�Ƕ�
  fp32 chassis_pitch; //�����Ǻ���̨������ӵ�pitch�Ƕ�
  fp32 chassis_roll;  //�����Ǻ���̨������ӵ�roll�Ƕ�

} chassis_move_t;
	 
void Chassis_Task(void const * argument);	 
	 
#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */
