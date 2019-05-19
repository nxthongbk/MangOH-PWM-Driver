# Integrate The Grove - 16-Channel PWM Driver with MangoH and Grove IoT Exapansion Card

This project demonstrates how to integrate The Grove - 16-Channel PWM Driver  with MangoH and Grove IoT Exapansion Card.


## Prerequisites

* A mangOH Red board.
* A Grove IoT Expansion card.
* The Grove - 16-Channel PWM Driver: See detail information on wiki page: http://wiki.seeedstudio.com/Grove-16-Channel_PWM_Driver-PCA9685/ 

<img src="https://user-images.githubusercontent.com/17214533/57985768-012eb780-7a97-11e9-8e96-95885f42e06c.jpg" width="350" alt="accessibility text"> 

The Grove - 16-Channel PWM Driver
------------------
The Grove - 16-Channel PWM Driver is based on NXP PCA9685, which is a 16-Channel, 12 bit I2C PWM driver. This board can drive up to 16 servos with the external power supply.


Legato Application
------------------
There are 3 legato applications:
* ```pwmDriver```: provides api for chosing interface and controling angle on 16-Channel PWM Driver.
* ```pwmDatahub```: push interface and angle value to datahub.
* ```pwmControl```: register for notification of value updates, create observation (filter) for PWM Driver and display the interface and angle value.


## Setup
1. Insert Grove IoT Expansion card into Mangoh Red
1. Jump 5V Pin on Grove IoT Card
1. Connect 16-Channel PWM Driver with I2C connector on Grove card



## How To Run

1. Build the pwmDriver app by running ```mkapp -t wp85 pwmDriver.adef``` in datahubPwm directory.
1. Run ```instapp pwmDriver.wp85.update 192.168.2.2``` to install the app.
1. Build the pwmDatahub app by running ```mkapp -t wp85 pwmDatahub.adef``` in datahubPwm directory.
1. Run ```instapp pwmDatahub.wp85.update 192.168.2.2``` to install the app.
1. Build the pwmControl app by running ```mkapp -t wp85 pwmControl.adef``` in datahubPwm directory.
1. Run ```instapp pwmControl.wp85.update 192.168.2.2``` to install the app.
