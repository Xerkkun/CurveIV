import processing.serial.*;

Serial myPort;

float voltaje = 0;        
float corriente = 0;      
PrintWriter output;
void setup() 
{
  size(700, 400);
  output = createWriter("curvaIV.dat");
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);

  //Generate a new serial event at new  line:
  myPort.bufferUntil('\n');
}

void draw() 
{
  println(voltaje + "," + corriente);  //Print serial data to terminal
  background(150);  //Standard grey background

  stroke(0);  //Base level line color
  line(0, 300, width, 300);  //Base level line

  noStroke();  //Remove outline

  fill(255, 0, 0);  //Volt rectangle
  rect(100, 300, 100, -voltaje);

  fill(0, 0, 255);  //Current rectangle
  rect(500, 300, 100, -corriente);
  fill(0);    //black
  textAlign(CENTER);

  text("humidity: "+voltaje, 150, 325);
  text("Temperature: "+corriente, 550, 325);
  output.println(voltaje + "," + corriente);
}



void serialEvent(Serial myPort)
{
  String inString = myPort.readStringUntil('\n');

  if (inString != null) 
  {
    inString = trim(inString);
    float[] vals = float(split(inString, ","));

    if (vals.length >= 2) 
    {
      voltaje = map(vals[0], 0, 1023, 0, 200);
      corriente = map(vals[1], 0, 1023, 0, 200);
    }
  }
}
void keyPressed()
{
  if (keyCode == UP)
  {
    output.flush(); //flush the buffer and
    //collect what data is on its way
    output.close(); //close the text file
  }
}