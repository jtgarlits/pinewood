# Project Summary
The goals of this project are to create a pinewood derby timing system that will
provide more insightful data to users, allow users to view this data on the web in real-time,
and, allow spectators to remotely experience a pinewood derby. In 2021, many events are
being held virtually to help maintain social distancing practices amidst our current
pandemic. Our track will allow pinewood derby race tournaments to effectively allow this,
making it safe and easy for parents, grandparents, and any other spectators to watch these
events and not miss out.
To achieve this goal, we built a 32-foot long wooden pinewood derby track that has
12 IR transmitter/receiver sensors built into the track to time the cars as they pass, as well
as a limit switch on the lift gate to obtain a start time. The data collected from these
sensors is collected by an Arduino using a 46-state state machine, processed, and sent
over WiFi to a database hosted on Google Firebase. A website (trinepinewood.com /
trine-pinewood.web.app), also hosted on Google Firebase, then pulls this data and
displays it. On the website, you can see times at speeds of both cars at two intermittent
checkpoints, as well as at the finish line. All of this happens autonomously and in real time,
so anyone can view live results anywhere in the world within seconds of the race ending.
Pairing this with a Zoom meeting allows the spectators to also watch the race live,
providing a full pinewood derby viewing experience.
We wanted to design an automatic timer for pinewood derby races to reduce
possible human error. These errors could result in naming the wrong winner or not
providing the correct time for the participants. Our timer can accurately measure down to
the microsecond to help racers optimize their car’s performance.


# Pinewood Assembly Instructions
1. Assemble the track - this can be done by sliding the pieces of the track together.
The ends are numbered, so make sure you match the ends up correctly. Before
screwing the track together, run the wire cable underneath the track and connect
the wires (red to W pin, blue to R pin, black to B pin). Once the pieces are together,
you need to screw them down.
2. Plug in the power strip that provides power to the Arduino and terminal blocks.
Connect the laptop to the Arduino and second screen. Go to
https://github.com/jtgarlits/pinewood/blob/main/Arduino/pinewood.ino and
download this file. If you do not have the Arduino IDE on your laptop, you will need
to download it. Open the pinewood.ino file, input your WiFi SSID and Password
where prompted on lines 16 and 17, and upload this file to your Arduino.
3. Display the website trinepinewood.com on the second screen, and you are ready to
race. To start a race, just place two cars at the top of the track, make sure the limit
switch is closed, and then raise the lift gate.
