import { connect } from "mqtt";

const client = connect('mqtt://broker.mqttdashboard.com')

client.on('connect', function(){
    client.subscribe('sarim/esp8266/dht11/temperature');
    client.subscribe('sarim/esp8266/dht11/humidity');
})
client.on('message', function (topic, message) {
    // message is Buffer
    // console.log("Temperature");
    console.log(topic.toString());
    console.log(message.toString());
});
