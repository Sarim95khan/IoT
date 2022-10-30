import { connect } from 'mqtt'

const client = connect('mqtt://broker.mqttdashboard.com')

client.on('connect', function(){
    client.subscribe('sarim/room/led');
})
client.on('message', function (topic, message) {
    // message is Buffer
    console.log(message.toString());
});
