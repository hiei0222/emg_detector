int max_analog_dta      = 300;              // max analog data
int min_analog_dta      = 100;              // min analog data
int static_analog_dta   = 0;                // static analog data


// get analog value
int getAnalog(int pin)
{
    long sum = 0;
    
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pin);
    }
    
    int dta = sum>>5;
    
    max_analog_dta = dta>max_analog_dta ? dta : max_analog_dta;         // if max data
    min_analog_dta = min_analog_dta>dta ? dta : min_analog_dta;         // if min data
    
    return sum>>5;
}
int blevel;
void setup()
{
    Serial.begin(115200);
    
    long sum = 0;

    for(int i=0; i<=10; i++)
    {
        for(int j=0; j<100; j++)
        {
            sum += getAnalog(A0);
            delay(1);
        }
        blevel = 10 -i;
    }
    
    sum /= 1100;
    
    static_analog_dta = sum;

    //Serial.print("static_analog_dta = ");
    //Serial.println(static_analog_dta);
}

int level       = 100;
int level_buf   = 100;


void loop()
{

    int val = getAnalog(A0);                    // get Analog value
    
    int level2;
    
    if(val>static_analog_dta)                   // larger than static_analog_dta
    {
        level2 = 100 + map(val, static_analog_dta, max_analog_dta, 0, 100);
    }
    else 
    {
        level2 = 100 - map(val, min_analog_dta, static_analog_dta, 0, 100);
    }
    
    // to smooth the change of led bar
    if(level2 > level)
    {
        level++;
    }
    else if(level2 < level)
    {
        level--;
    }

    if(level != level_buf)
    {
        level_buf = level;
        blevel = level;
    }
    
    Serial.println(blevel);
    delay(10);
}
