# Echo-Meter


## *Problem intended to be solved :*
<ul>
  <li>As a result of population and globalization, the environment is being polluted in many ways. Air and 
Sound pollution are major pollutions which is according to United Nations reports.<br> There were 4.2 
million deaths due to air pollution. <br>To reduce this pollution people must know the real time pollution 
status and how they can reduce it. 
    

</li> <br>
  <li>The purpose of this project is to implement a platform to find AIR Quality index and Noise level in a 
place where this system is implemented. Client can get those informations through the web page.</li> <br>
 
</ul>

## *System overview and Operation :*
<ul>
  <li>Technology Stack
</li> <br>
  <code><img height = 200 src="https://github.com/ViduraErandika/Echo-Meter/blob/main/images/stack.jpg"></code> <br>
 
</ul>

## *Hardware, software flow, protocols, online resources used :*
<ul>
  <li>Node-red</li>
  <p>Node-RED provides a browser-based flow editor that makes it easy to wire together flows using the wide range 
of nodes in the palette. Flows can be then deployed to the runtime in a single-click. JavaScript functions can be 
created within the editor using a rich text editor. A built-in library allows you to save useful functions, templates 
or flows for re-use. Node-RED is built on Node.js, taking full advantage of its event-driven, non-blocking model. 
This makes it ideal to run at the edge of the network on low-cost hardware such as the Raspberry Pi as well as in 
the cloud.</p>
  <li>MQTT broker</li>
  <p>MQTT is a lightweight, publish-subscribe network protocol that transports messages between devices. The 
protocol usually runs over TCP/IP; however, any network protocol that provides ordered, lossless, bi-directional 
connections can support MQTT. It is designed for connections with remote locations where a "small code 
footprint" is required or the network bandwidth is limited.</p>
  
  <li>Node-MCU</li>
  <p>Node-MCU is an open source firmware for which open source prototyping board designs are available. The 
prototyping hardware typically used is a circuit board functioning as a dual in-line package (DIP) which integrates 
a USB controller with a smaller surface-mounted board containing the MCU and antenna. The choice of the DIP 
format allows for easy prototyping on breadboards. The design was initially based on the ESP-12 module of 
the ESP8266, which is a Wi-Fi SoC integrated with a Tensilica-Xtensa LX106 core, widely used in IoT 
applications.</p>
  
  <li>Open-source API</li><br>
  <p>Air pollution API - <a href="https://openweathermap.org/api/air-pollution"> https://openweathermap.org/api/air-pollution </a> <p>
  <p>Air Pollution API provides current, forecast and historical air pollution data for any coordinates on the globe. 
Besides basic Air Quality Index, the API returns data about polluting gases, such as Carbon monoxide (CO), 
Nitrogen monoxide (NO), Nitrogen dioxide (NO2), Ozone (O3), Sulphur dioxide (SO2), Ammonia (NH3), and 
particulates (PM2.5 and PM10).</p>
  
  <li>Voice Sound Detection Mic Sensor Module (MD0220)</li>
  <p>This sensor module gives real time analog output voltage signal of the microphone.</p> 
</ul>

## *OUTCOMES :*
<ul>
  <li>User can get air quality index any place in the world
</li> <br>
 <li>User can receive noise level in a place where the system is implemented.
</li> <br>
  <li>Any device that has ability to connect to the webserver
</li> <br>
</ul>
