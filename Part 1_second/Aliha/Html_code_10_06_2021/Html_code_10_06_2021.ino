#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// Set these to your desired credentials.
const char *ssid = "princeAP1";
const char *password = "superlab";

long var1 = 300;
long var2 = 500;


WiFiServer server(80);

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {

          
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<script type=\"text/javascript\">");
          client.println("window.onload = function() {");
          client.println("httpGetAsync(\"/value1\");");
          client.println("function httpGetAsync(theUrl) { ");
          client.println("var xmlHttp = new XMLHttpRequest();");
          client.println("var frequency_val = 1000;");
          client.println("xmlHttp.onreadystatechange = function() { ");
          client.println("if (xmlHttp.readyState == 4 && xmlHttp.status == 200)");
          client.println("document.getElementById(\"val\").innerHTML = xmlHttp.responseText; }");
          client.println("xmlHttp.open(\"GET\", theUrl, true); ");
          client.println("xmlHttp.send(null)");
          client.println("setTimeout(function(){httpGetAsync(\"/value1\")}, frequency_val); } }");
          client.println("</script>");
          client.println("</head>");
          client.println("<body>");
          client.print("<p style=\"font-size: 70px; font-style: arial; display: center; text-align:center; color:black\">PRODUCTIVITY TIMER</p> <br>");
          client.println("<h2 style=\"font-size: 64px; font-style: arial; display: center; text-align: center; color: gray\"> Time Left: </h2> ");
          client.println("<h2 id=\"val\" style=\"font-size: 64px; display: center; text-align : center; color:maroon\"> </h2> <br>");
          client.print("<p style=\"font-size: 50px; display: center; text-align : center; color:black\"><a href=\"/home\">Reset</a> </p> <br>");
          client.println("</body>");
          client.println("</html>");
        }
        if (currentLine.endsWith("GET /L")) {
          
         
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<script type=\"text/javascript\">");
          client.println("window.onload = function() {");
          client.println("httpGetAsync(\"/value2\");");
          client.println("function httpGetAsync(theUrl2) { ");
          client.println("var xmlHttp2 = new XMLHttpRequest();");
          client.println("var frequency_val = 1000;");
          client.println("xmlHttp2.onreadystatechange = function() { ");
          client.println("if (xmlHttp2.readyState == 4 && xmlHttp2.status == 200)");
          client.println("document.getElementById(\"val\").innerHTML = xmlHttp2.responseText; }");
          client.println("xmlHttp2.open(\"GET\", theUrl2, true); ");
          client.println("xmlHttp2.send(null)");
          client.println("setTimeout(function(){httpGetAsync(\"/value2\")}, frequency_val); } }");
          client.println("</script>");
          client.println("</head>");
          client.println("<body>");
          client.print("<p style=\"font-size: 70px; font-style: arial; display: center; text-align:center; color:black\">BREAK TIMER</p> <br>");
          client.println("<h2 style=\"font-size: 64px; font-style: arial; display: center; text-align: center; color: gray\"> Time Left: </h2> ");
          client.println("<h2 id=\"val\" style=\"font-size: 64px; display: center; text-align : center; color:maroon\"> </h2> <br>");
          client.print("<p style=\"font-size: 50px; display: center; text-align : center; color:black\"><a href=\"/home\">Reset</a> </p> <br>");
          client.println("</body>");
          client.println("</html>"); 
        
        }

        if (currentLine.endsWith("GET /home")) {
          Serial.println("Home");

          // html and javascript code sent to the browser
          /*

            <!DOCTYPE HTML>
            <html>
            <head>
            <script type="text/javascript">
            window.onload = function() {
            httpGetAsync("/value");
            function httpGetAsync(theUrl) {
            var xmlHttp = new XMLHttpRequest();
            var frequency_val = 1000;
            xmlHttp.onreadystatechange = function() {
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
                document.getElementById("val").innerHTML = xmlHttp.responseText; }
            xmlHttp.open("GET", theUrl, true);
            xmlHttp.send(null);

            setTimeout(function(){httpGetAsync("/value")}, frequency_val); } }
            </script>

            </head>
            <body>
            <h2 style="font-size: 38px; display: inline; color: gray">LEVEL: </h2>
            <h2 id="val" style="font-size: 36px; display: inline; color:maroon"> </h2>
            <p style=\"font-size: 36px; display: inline; color:blue\">Click <a href=\"/H\">here</a> to turn ON the LED.</p> <br>
            <p style=\"font-size: 36px; display: inline; color:green\">Click <a href=\"/L\">here</a> to turn OFF the LED.</p> <br>

            </body>
            </html>

          */

          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<body>");
          client.print("<p style=\"font-size: 70px; font-style: verdana; display: center; text-align:center; color:maroon\">POMODORO TIMER</p> <br>");
          client.print("<p style=\"font-size: 20px; display: inline; color:black\">The Pomodoro technique is a tool used to boost time management introduced by Francesco Cirillo in the late 1980s. The technique suggests a productive period of  twenty-five mintutes followed by a short break. Each interval is known as a pomodoro from the Italian word for tomato and this name was given after Cirillo's tomato-shaped kitchen timer which he used while in university.  </p> <br>");
          client.print("<p style=\"font-size: 40px; display: center; color:maroon\"> TIMER 1 </p> <br>");
          
        
          client.print ("<form action=\"/H.php\">");
          client.println ("<label for =\"t1value\"; style=\"font-size: 30px; display: inline; color:black\">Please set Timer 1</label> <br>");
          client.print ("<input type=\"text\"; id=\"t1value\"; name=\"t1value\" > </input> <br>");
          client.print (" <input type=\"submit\"; onclick =\"getvalue()\"></input> ");
          client.println ("</form>");
         
        

          client.print("<p style=\"font-size: 40px; display: center; color:maroon\"> TIMER 2 </p> <br>");
          client.print ("<form action=\"/L.php\">");
          client.println ("<label for =\"t2value\"; style=\"font-size: 30px; display: inline; color:black\">Please set Timer 2</label> <br>");
          client.print ("<input type=\"text\"; id=\"t2value\"; name=\"t2value\" > </input> <br>");
          client.print (" <input type=\"submit\" ></input> ");
         
          client.println ("</form>");
          client.println("</body>");
          client.println("</html>");
        }

        

        if (currentLine.endsWith("GET /value1")) {
         
          var1--;
          Serial.println(var1);
          client.println(var1);
          
        }
      
      if (currentLine.endsWith("GET /value2")) {
         
          var2--;
          Serial.println(var2);
          client.println(var2);
          
        }
        
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
