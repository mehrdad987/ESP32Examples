#define RXD2 34
#define TXD2 32
String out[20],out1[20],out2[20],out3[20];
char gp;
void setup(void) {
  
  Serial.begin(115200);

  Serial2.begin(4800, SERIAL_8N1, RXD2, TXD2);


}
 
void loop(void) { //Choose Serial1 or Serial2 as required

  delay(500);
  if (Serial2.available()) {
    char gdata = (char(Serial2.read()));
    while(gp != 'G' ){ 
      gp = (char(Serial2.read()));
    }
    gp = (char(Serial2.read()));
    while(gp != 'P'){ 
      gp = (char(Serial2.read()));
    }
    gp = (char(Serial2.read()));
    while(gp != 'R'){    
      gp = (char(Serial2.read()));
    }
    gp = (char(Serial2.read()));
    while(gp != 'M'){  
      gp = (char(Serial2.read()));
    }
    gp = (char(Serial2.read()));
      if(gp == 'C'){
        gp = (char(Serial2.read()));        
        for (int i0 = 0; i0 <= 15; i0++) { 
          gdata = (char(Serial2.read()));
          if(gdata == 'A'){
            i0=15;
            for(int i1 = 0; i1 <= 15; i1++) {
              char gdata = (char(Serial2.read()));
              String str(gdata);
              out[i1]= out[i1]+str;Serial.print(out[i1]);
              if(gdata == 'N'||gdata == 'S'){
                Serial.println("");
                i1=15;
                for(int i2 = 0; i2 <= 15; i2++) {
                  char gdata = (char(Serial2.read()));
                  out[i2]= out[i2]+gdata;
                  if(gdata == 'W'||gdata == 'E'){
                    i2=15;
                    for(int i3 = 0; i3 <= 5; i3++) {
                      char gdata = (char(Serial2.read()));
                      out[i3]= out[i3]+gdata;
                      if(gdata == '.'){break;}
                      }
                    }
                  }
                }
              }
//          Serial.println(out[]);
////          out[]="";
//          Serial.println(out[]);
////          out[]="";
//          Serial.println(out[]);
////          out[]="";
          }
        }    

    }
  }
}
