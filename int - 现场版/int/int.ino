#include <Servo.h>

Servo servo_1;//左前轮
Servo servo_2;//右前轮
Servo servo_3;//左后轮
Servo servo_4;//右后轮
Servo servo_5;//前爪
Servo servo_6;//后爪

const unsigned char Tracker_Pin[5] = //寻迹引脚
{
  50,  //左1
  49,  //左2
  48,  //左3
  47,  //左4
  46   //左5
};

void Tracker_Begin() //寻迹初始化
{
  for (int i = 0; i < 5; i++)
    pinMode(Tracker_Pin[i], INPUT);
}

unsigned char Tracker_Read() //循迹读取
{
  unsigned char Value = 0x00;
  for (int i = 0; i < 5; i++)
    Value += ((!digitalRead(Tracker_Pin[i])) << (4 - i));
  return Value;
}

bool Read_All()
{
  if (Tracker_Read() == 0b11111)
    return true;
  else
    return false;
}

void Servo_Begin()//舵机初始化
{
  servo_1.attach(7);//左前轮
  servo_2.attach(6);//右前轮
  servo_3.attach(27);//左后轮
  servo_4.attach(26);//右后轮
  servo_5.attach(30);//前爪舵机
  servo_6.attach(31);//后爪舵机
  servo_1.write(90);
  servo_2.write(90);
  servo_3.write(90);
  servo_4.write(90);
  servo_5.write(5);//收回
  delay(400);
  servo_6.write(175);//收回
}

void qianjin()
{
  servo_1.write(180);
  servo_2.write(0);
  servo_3.write(174);
  servo_4.write(2);
}

void qianjinmin()
{
  servo_1.write(143);
  servo_2.write(42);
  servo_3.write(141);
  servo_4.write(43);
}

void houtui()
{
  servo_1.write(41);
  servo_2.write(143);
  servo_3.write(42);
  servo_4.write(141);
}

void zuozhuan()
{
  servo_1.write(143);
  servo_2.write(0);
  servo_3.write(141);
  servo_4.write(2);
}

void youzhuan()
{
  servo_1.write(180);
  servo_2.write(43);
  servo_3.write(176);
  servo_4.write(44);
}

void zuozhuanmax()
{
  servo_1.write(0);
  servo_2.write(0);
  servo_3.write(3);
  servo_4.write(3);
}

void youzhuanmax()
{
  servo_1.write(180);
  servo_2.write(180);
  servo_3.write(177);
  servo_4.write(177);
}

void tingche()
{
  servo_1.write(90);
  servo_2.write(90);
  servo_3.write(90);
  servo_4.write(90);
}

void qianzhua(int deg3)
{
  servo_5.write(deg3);
}

void houzhua(int deg4)
{
  servo_6.write(deg4);
}

void loop_1()//减速带
{
  qianjinmin();
  while (true)//先直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)
    {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)
    {
      zuozhuan();
      delay(40);
    }
    else if (T == 0b00100 || T == 0b01110 || T == 0b00000)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)
    {
      youzhuan();
      delay(40);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)
    {
      youzhuan();
      delay(80);
    }
    else if (T == 0b11111)
      break;
  }

  tingche();
  delay(1000);
  //正式开始
  servo_5.write(150);
  delay(400);
  for (int i = 0; i <= 30; i++)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)
    {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)
    {
      zuozhuan();
      delay(40);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)
    {
      youzhuan();
      delay(40);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)
    {
      youzhuan();
      delay(80);
    }
    delay(7);//循迹0.5s
  }
  tingche();
  delay(500);
  digitalWrite(35, HIGH);
  qianjinmin();
  delay(4370);//减速带时间
  while (true)
  {
    delay(10);
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)
    {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)
    {
      zuozhuan();
      delay(40);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)
    {
      youzhuan();
      delay(40);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)
    {
      youzhuan();
      delay(80);
    }
    else if (T == 0b11111)
      goto label;
  }
label:
  digitalWrite(35, LOW);
  servo_5.write(5);//收回
  delay(300);
  servo_6.write(175);//收回
  qianjinmin();
}

void loop_2()//草地
{
  for (int i = 0; i <= 450; i++)//！！！！！470orig
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001)  {
      youzhuan();
      delay(80);
    }
    delay(5);
  }
  qianjinmin();
  servo_5.write(150);
  digitalWrite(35, HIGH);
  delay(3900);
  digitalWrite(35, LOW);
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)
    {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)
    {
      zuozhuan();
      delay(40);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)
    {
      youzhuan();
      delay(40);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)
    {
      youzhuan();
      delay(80);
    }
    else if (T == 0b11111)
      break;
    else if (T == 0b00000)
    {
      while (1)
      {
        unsigned char T = 0x00;
        T = Tracker_Read();
        qianjinmin();
        if (T == 0b11111 || T == 0b01111 || T == 0b11110)//碰到横线
        {
          delay(50);
          break;
        }
      }
      zuozhuanmax();
      delay(690);
      qianjinmin();
      while (true)
      {
        unsigned char T = 0x00;
        T = Tracker_Read();
        if      (T == 0b10000 || T == 0b11000 || T == 0b11100)
        {
          zuozhuan();
          delay(80);
        }
        else if (T == 0b01000 || T == 0b01100)
        {
          zuozhuan();
          delay(40);
        }
        else if (T == 0b00100 || T == 0b01110)  qianjinmin();
        else if (T == 0b00110 || T == 0b00010)
        {
          youzhuan();
          delay(40);
        }
        else if (T == 0b00011 || T == 0b00001 || T == 0b00111)
        {
          youzhuan();
          delay(80);
        }
        else if (T == 0b11111)
          break;
      }
      qianjinmin();
      delay(100);
      youzhuanmax();
      delay(670);
    }
  }
  tingche();
  digitalWrite(35, LOW);
  servo_5.write(5);
  delay(400);
}

void loop_3()//方形隧道
{
  qianjinmin();
  delay(200);
  while (true)//先直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000)
      break;
  }
  tingche();
  delay(300);
  { //后退一点点,slower than houtui();
    servo_1.write(66);
    servo_2.write(118);
    servo_3.write(67);
    servo_4.write(116);
  }
  delay(70);
  tingche();
  zuozhuanmax();//左转
  delay(650);//是否刮大型阶梯就看它
  qianjinmin();
  delay(100);
  while (true)//再直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(30);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(30);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000)
      break;
  }
  youzhuanmax();//右转
  delay(650);
  qianjinmin();
  delay(100);


  int i = 0;
  while (i < 120) //先直行,没进隧道
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b00000)
      break;
    i++;
    delay(9);
  }

  while (true)//进隧道
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000 || T == 0b00010)
      break;
  }
  tingche();
  delay(300);
  { //后退一点点,slower than houtui();
    servo_1.write(66);
    servo_2.write(118);
    servo_3.write(67);
    servo_4.write(116);
  }
  delay(68);//!!!!!!!!!!!!!!!!!!比赛场地上市68
  zuozhuanmax();//左转
  delay(650);//比赛场地上市650
  qianjinmin();
  delay(200);
  while (true)//后半段隧道循迹
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(30);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110)  {
      youzhuan();
      delay(30);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000 || T == 0b00010)
      break;
  }
  tingche();
  delay(300);
  { //后退一点点,slower than houtui();
    servo_1.write(66);
    servo_2.write(118);
    servo_3.write(67);
    servo_4.write(116);
  }
  delay(68);//!!!!!!!!!!!!!!!!!!!比赛场地上市68
  zuozhuanmax();//左转
  delay(650);//!!!!!!!!!!!!!!!!!!!比赛场地上市655
  qianjinmin();
  delay(200);
  while (true)//再直行，出隧道
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(30);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(30);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000)
      break;
  }
  tingche();
  delay(200);
  { //后退一点
    servo_1.write(62);
    servo_2.write(114);
    servo_3.write(63);
    servo_4.write(116);
  }
  delay(90);
  tingche();
  delay(200);
  youzhuanmax();//右转
  delay(633);//这个数得调
  qianjinmin();
  delay(100);
  while (true)//先直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(30);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(30);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000)
      break;
  }
  zuozhuanmax();//左转
  delay(670);
  qianjinmin();
  delay(100);
  while (true)//走完了，直行到十字路口
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(30);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(30);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b11111)//到十字路口
      break;
  }
  qianjinmin();
  delay(100);
  youzhuanmax();
  delay(670);
  qianjinmin();
}

void loop_4()//U形隧道
{
  qianjinmin();
  delay(150);
  while (true)//走完了，直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000)
      break;
  }
  { //后退一点点,slower than houtui();
    servo_1.write(66);
    servo_2.write(118);
    servo_3.write(67);
    servo_4.write(116);
  }
  delay(160);
  zuozhuanmax();//左转
  delay(550);//523+
  qianjinmin();
  delay(150);
  while (true)//再直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(20);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(20);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b00000)
      break;
  }

  youzhuanmax();//右转
  delay(670);
  qianjinmin();
  delay(300);
  int i = 0;
  while (i < 110) //准备进入隧道
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000)  break;
    else if (T == 0b01000 || T == 0b01100 || T == 0b11100)  {
      zuozhuan();
      delay(60);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(60);
    }
    i++;
    delay(9);
  }
  while (true)//进入隧道的循迹
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    servo_1.write(108);
    servo_2.write(57);
    servo_3.write(106);
    servo_4.write(58);
    if (T == 0b00000)
      break;
  }
  youzhuanmax();//右转
  delay(670);
  qianjinmin();
  delay(200);
  while (true)//直行，进入循迹准备道
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000)
      break;
  }
  zuozhuanmax();//左转
  delay(670);
  qianjinmin();
  delay(400);
}

void loop_5()//栅格
{
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b11111)
      break;
  }
  qianjinmin();//人为推测
  delay(95);
  youzhuanmax();//右转，进入栅格准备道
  delay(670);
  qianjinmin();
  delay(500);
  int i = 0;
  while (i < 100) //栅格准备道循迹1s
  {
    i++;
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b11111)
      break;
    delay(10);
  }
  tingche();
  delay(150);
  servo_5.write(180);//上栅格
  delay(300);
  digitalWrite(35, HIGH);
  qianjinmin();
  delay(700);
  tingche();
  servo_5.write(150);
  servo_6.write(5);//后爪
  delay(300);
  qianjin();
  delay(500);
  servo_6.write(100);//后爪放下
  delay(2800);//走栅格
  tingche();
  digitalWrite(35, LOW);
  servo_5.write(5);//收回
  delay(400);
  servo_6.write(175);//收回
  delay(200);
  for (int i = 0; i < 130; i++)//落地循迹
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    delay(9);
  }
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b00000)
      break;
  }
  tingche();
  delay(100);
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    houtui();
    if (T == 0b10000 || T == 0b11000 || T == 0b11100 || T == 0b11110)
      break;
  }
  tingche();
  delay(300);
  qianjinmin();
  delay(310);
  zuozhuanmax();//左转，进入一段长直线
  delay(670);
  qianjinmin();
  delay(600);
  while (true)//左转长直线循迹
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(90);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(90);
    }
    else if (T == 0b00000)
      break;
  }
  zuozhuanmax();//左转，进入一段长直线(一半场地长)
  delay(670);
  qianjinmin();
  delay(660);
}

void loop_6()//小阶梯
{
  while (true)//先直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b11111)
      break;
  }
  qianjinmin();
  delay(100);
  zuozhuanmax();//左转，进入小阶梯预备道
  delay(670);
  qianjinmin();
  delay(650);
  int i = 0;
  while (i < 80) //台阶准备道循迹0.6s
  {
    i++;
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b00000)
      break;
    delay(7);
  }
  //开始上台阶
  tingche();
  delay(300);
  servo_5.write(175);//放前爪
  digitalWrite(35, HIGH);
  delay(300);
  qianjinmin();
  delay(800);
  tingche();//前轮已上
  delay(100);
  servo_6.write(5);//放后爪
  delay(100);
  servo_5.write(5);//收前爪
  delay(100);
  qianjinmin();
  delay(700);
  tingche();
  servo_6.write(175);//收后爪
  servo_5.write(175);//放前爪
  qianjinmin();
  delay(800);
  tingche();
  servo_6.write(5);//放后爪
  delay(300);
  qianjinmin();
  delay(400);
  digitalWrite(35, LOW);
  servo_5.write(130);//前爪调平位
  servo_6.write(80);//后爪调平位
  delay(2000);
  tingche();//已经下台阶
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(50);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(50);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b11111)
      break;
  }
  delay(600);
}

void loop_7()//防滑带
{
  int i = 0;
  while (i < 137) //过第一个采样点，再循迹1.5s
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(75);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(35);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(35);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(75);
    }
    i++;
    delay(9);
  }
  tingche();
  digitalWrite(35, HIGH);
  servo_5.write(178);
  delay(250);
  qianjinmin();
  delay(300);
  servo_5.write(130);//前爪调平位
  delay(300);
  servo_6.write(130);//后爪蹬
  delay(550);
  servo_6.write(80);//后爪调平位
  qianjinmin();
  delay(2990);//走完防滑带？？？
  digitalWrite(35, LOW);
littlee:
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(100);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(100);
    }
    else if (T == 0b11111)
      break;
    else if (T == 0b00000)
    {
      while (true)
      {
        unsigned char T = 0x00;
        T = Tracker_Read();
        houtui();
        if (T != 0b00000)
        {
          delay(1000);
          goto littlee;
        }
      }
    }
  }
  qianjinmin();
  delay(110);
  tingche();
  delay(250);
  youzhuanmax();//右转，进入窄桥准备道
  delay(521);
  { //后退一点点,slower than houtui();
    servo_1.write(66);
    servo_2.write(118);
    servo_3.write(67);
    servo_4.write(116);
  }
  delay(1500);
  servo_5.write(127);//前爪调平位
  servo_6.write(80);//后爪调平位
  { //slower than qianjinmin();
    servo_1.write(128);
    servo_2.write(57);
    servo_3.write(126);
    servo_4.write(58);
  }
}

void loop_8()//窄桥
{
  digitalWrite(35, HIGH);
  //int i = 0;
  while (true) //过第一个采样点，再循迹1.2s
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(60);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(10);
    }
    else if (T == 0b00100 || T == 0b01110)
    { //slower than qianjinmin();
      servo_1.write(128);
      servo_2.write(57);
      servo_3.write(126);
      servo_4.write(58);
    }
    else if (T == 0b00110 || T == 0b00010)
    {
      youzhuan();
      delay(10);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)
    {
      youzhuan();
      delay(60);
    }
    else if (T == 0b00000 || 0b11111)
      break;
  }
  //  while (true)
  //  {
  //    delay(10);
  //    unsigned char T = 0x00;
  //    T = Tracker_Read();
  //    if (T == 0b00100 || T == 0b01110 || T == 0b01100 || T == 0b00110 || T == 0b11000 || T == 0b00011)
  //      break;
  //  }
  { //slower than qianjinmin();
    servo_1.write(128);
    servo_2.write(57);
    servo_3.write(126);
    servo_4.write(58);
  }
  delay(6300);//走窄桥
}

void loop_9()//上大阶梯
{
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    { //slower than qianjinmin();
      servo_1.write(128);
      servo_2.write(57);
      servo_3.write(126);
      servo_4.write(58);
    }
    if (T == 0b11111)
      break;
  }
  delay(280);
  youzhuanmax();//左转，进入大阶梯预备道
  delay(670);
  qianjinmin();
  delay(360);
  int i = 0;
  while (i < 80) //台阶准备道循迹0.6s
  {
    i++;
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b00000)
      break;
    delay(7);
  }
  //开始上台阶
  tingche();
  delay(300);
  digitalWrite(35, HIGH);
  delay(300);
  qianjinmin();
  delay(600);
  tingche();//前轮已上
  delay(100);
  servo_6.write(5);//放后爪
  delay(100);
  delay(100);
  qianjinmin();
  delay(500);
  tingche();//第一次OK
  servo_6.write(175);//收后爪
  qianjinmin();
  delay(500);
  tingche();
  servo_6.write(5);//放后爪
  delay(300);
  qianjinmin();
  delay(500);
  tingche();//第二次OK
  servo_6.write(175);//收后爪
  qianjinmin();
  delay(500);
  tingche();
  servo_6.write(5);//放后爪
  delay(300);
  qianjinmin();
  delay(550);
  tingche();//第三次OK
  digitalWrite(35, LOW);
  servo_6.write(175);//收后爪
  { //右转，高台准备
    servo_1.write(128);
    servo_2.write(128);
    servo_3.write(126);
    servo_4.write(126);
  }
  delay(1333);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void loop_10()//上平台&后退
{
  {
    //slower than qianjinmin();
    servo_1.write(128);
    servo_2.write(57);
    servo_3.write(126);
    servo_4.write(58);
  }
  delay(650);
  tingche();
  delay(300);
  servo_5.write(145);//放前爪145
  { //slower than qianjinmin();
    servo_1.write(128);
    servo_2.write(57);
    servo_3.write(126);
    servo_4.write(58);
  }
  delay(400);
  servo_5.write(180);//放全部前爪
  delay(200);
  servo_6.write(3);//放后爪
  delay(700);
  servo_5.write(130);//前爪调平位
  delay(2000);
  servo_6.write(80);//后爪调平位
  tingche();
  delay(300);

  //  { //掉头
  //    servo_1.write(128);
  //    servo_2.write(128);
  //    servo_3.write(126);
  //    servo_4.write(126);
  //  }
  //  delay(1740);
}

void loop_11()//下平台+阶梯
{
  {
    servo_1.write(62);
    servo_2.write(114);
    servo_3.write(63);
    servo_4.write(116);
  }
  delay(4550);//后退下高台
  tingche();
  delay(300);
  { //左转，下高台准备
    servo_1.write(53);
    servo_2.write(53);
    servo_3.write(54);
    servo_4.write(54);
  }
  delay(940);
  //slower than qianjinmin();
  servo_1.write(128);
  servo_2.write(57);
  servo_3.write(126);
  servo_4.write(58);
  servo_5.write(155);//放前爪140
  digitalWrite(35, HIGH);
  delay(3900);
  tingche();
}

void loop_12()//石子路
{
  while (true)//再直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b11111)
      break;
  }
  delay(400);
  int i = 0;
  while (i < 130) //再直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b11111)
      break;
    delay(9);
    i++;
  }
  qianjinmin();
  delay(7000);
  tingche();
  delay(60000);
}

void loop_5X()//栅格
{
  qianjin();
  delay(300);
  int i = 0;
  while (i < 210) //栅格准备道循迹2.3s
  {
    i++;
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010 || T == 0b00111)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 )  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b11111)
      break;
    delay(10);
  }
  tingche();
  delay(150);
  servo_5.write(180);//上栅格
  delay(300);
  digitalWrite(35, HIGH);
  qianjinmin();
  delay(700);
  tingche();
  servo_5.write(150);
  servo_6.write(5);//后爪
  delay(300);
  qianjin();
  delay(500);
  servo_6.write(100);//后爪放下
  delay(2800);//走栅格
  tingche();
  digitalWrite(35, LOW);
  servo_5.write(5);//收回
  delay(400);
  servo_6.write(175);//收回
  delay(200);
  while (true)//落地循迹
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b11111)
      break;
  }
  delay(90);
  youzhuanmax();//右转，进入防滑带
  delay(670);
  qianjinmin();
  delay(600);
}

void loop_7X()//防滑带
{
  int i = 0;
  while (i < 137) //过第一个采样点，再循迹1.5s
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(75);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(35);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(35);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(75);
    }
    i++;
    delay(9);
  }
  tingche();
  digitalWrite(35, HIGH);
  servo_5.write(178);
  delay(250);
  qianjinmin();
  delay(300);
  servo_5.write(130);//前爪调平位
  delay(300);
  servo_6.write(130);//后爪蹬
  delay(550);
  servo_6.write(80);//后爪调平位
  qianjinmin();
  delay(2990);//走完防滑带？？？
  digitalWrite(35, LOW);
littlee:
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(100);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(100);
    }
    else if (T == 0b11111)
      break;
    else if (T == 0b00000)
    {
      while (true)
      {
        unsigned char T = 0x00;
        T = Tracker_Read();
        houtui();
        if (T != 0b00000)
        {
          delay(1000);
          goto littlee;
        }
      }
    }
  }
  qianjinmin();
  servo_5.write(5);
  servo_6.write(175);
}

void loop_6X()//小阶梯
{
  int i = 0;
  while (i < 170) //台阶准备道循迹0.6s
  {
    i++;
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(70);
    }
    else if (T == 0b01000 || T == 0b01100)  zuozhuan();
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  youzhuan();
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(70);
    }
    else if (T == 0b00000)
      break;
    delay(7);
  }
  //开始上台阶
  tingche();
  delay(300);
  servo_5.write(175);//放前爪
  digitalWrite(35, HIGH);
  delay(300);
  qianjinmin();
  delay(800);
  tingche();//前轮已上
  delay(100);
  servo_6.write(5);//放后爪
  delay(100);
  servo_5.write(5);//收前爪
  delay(100);
  qianjinmin();
  delay(700);
  tingche();
  servo_6.write(175);//收后爪
  servo_5.write(175);//放前爪
  qianjinmin();
  delay(800);
  tingche();
  servo_6.write(5);//放后爪
  delay(300);
  qianjinmin();
  delay(400);
  digitalWrite(35, LOW);
  servo_5.write(130);//前爪调平位
  servo_6.write(80);//后爪调平位
  delay(2000);
  tingche();//已经下台阶
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(50);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(50);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b11111)
      break;
  }
  delay(150);
}

void spec()
{
  youzhuanmax();
  delay(520);
  qianjinmin();
  delay(100);
  while (true)//先直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(20);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(20);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b00000)
      break;
  }
  tingche();
  delay(300);
  { //后退一点点,slower than houtui();
    servo_1.write(66);
    servo_2.write(118);
    servo_3.write(67);
    servo_4.write(116);
  }
  delay(70);
  tingche();
  youzhuanmax();//左转
  delay(520);
  qianjinmin();
  delay(100);
  while (true)//再直行
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    if      (T == 0b10000 || T == 0b11000 || T == 0b11100)  {
      zuozhuan();
      delay(80);
    }
    else if (T == 0b01000 || T == 0b01100)  {
      zuozhuan();
      delay(20);
    }
    else if (T == 0b00100 || T == 0b01110)  qianjinmin();
    else if (T == 0b00110 || T == 0b00010)  {
      youzhuan();
      delay(20);
    }
    else if (T == 0b00011 || T == 0b00001 || T == 0b00111)  {
      youzhuan();
      delay(80);
    }
    else if (T == 0b11111)
      break;
  }
  delay(100);
  youzhuanmax();//右转
  delay(520);//!!!
  tingche();
  delay(100);
  while (true)
  {
    unsigned char T = 0x00;
    T = Tracker_Read();
    //后退一点点,slower than houtui();
    servo_1.write(66);
    servo_2.write(118);
    servo_3.write(67);
    servo_4.write(116);
    if (T == 0b11111)
      break;
  }
  delay(1000);
  tingche();
}

//void func1()//常规
//{
//  loop_1();//减速带
//  loop_2();//草地
//  loop_3();//直角隧道
//  loop_4();//U隧道
//  loop_5();//栅格
//  loop_6();//小阶梯
//  loop_7();//防滑带
//  loop_8();//窄桥
//  loop_9();//大阶梯
//  loop_10();//上高台
//  loop_11();//下高台
//  loop_12();//石子
//}
//
//void func2()//栅格-防滑带-小型阶梯-接原来
//{
//  loop_5X();
//  loop_7X();
//  loop_6X();
//  spec();
//  loop_1();//减速带
//  loop_2();//草地
//  loop_3();//直角隧道
//  loop_4();//U隧道
//  loop_5();//栅格
//  loop_6();//小阶梯
//  loop_7();//防滑带
//  loop_8();//窄桥
//  loop_9();//大阶梯
//  loop_10();//上高台
//  loop_11();//下高台
//  loop_12();//石子
//}

void setup()
{
  // pinMode(22, INPUT); //func1
  // pinMode(23, INPUT); //func2
  pinMode(7, OUTPUT); //左前轮
  pinMode(6, OUTPUT); //右前轮
  pinMode(26, OUTPUT); //左后轮
  pinMode(27, OUTPUT); //右后轮
  pinMode(30, OUTPUT); //前爪舵机
  pinMode(31, OUTPUT); //后爪舵机
  pinMode(34, OUTPUT); //继电器+
  pinMode(35, OUTPUT); //继电器-
  digitalWrite(34, LOW);//继电器+,后退
  digitalWrite(35, LOW);//继电器-,前进
  Servo_Begin();
  Tracker_Begin();
  Serial.begin(9600);
}

void loop()
{
  // 
  loop_1();//减速带
  loop_2();//草地
  loop_3();//直角隧道
  loop_4();//U隧道
  loop_5();//栅格
  loop_6();//小阶梯
  loop_7();//防滑带
  loop_8();//窄桥
  loop_9();//大阶梯
  loop_10();//上高台
  loop_11();//下高台
  loop_12();//石子
}
