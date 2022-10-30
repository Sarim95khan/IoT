import { connect } from "mqtt";


// const user_info = {clientID : 'sarim95server',
//                     username : 'sarim',
//                     password : 'good',

//                     }

const client = connect('mqtt://broker.mqttdashboard.com');

client.on('connect',function(){
    client.subscribe('sarim/plant/moisture',function(err){
        if(!err){
            client.publish('sarim/plant/message','Connected to moisture Sensor!') //publish: message
        }
    });

})
client.on('message',function(topic,message){
    // console.log(topic.toString);
    console.log(topic);
    console.log(message.toString());
    console.log(parseFloat(message));
    if (topic === 'sarim/plant/moisture' && parseFloat(message) > 60){
        client.publish('sarim/plant/message','Turning off pump')
        client.publish('sarim/plant/pump','OFF')
    }

    else if(topic ==='sarim/plant/moisture' && parseFloat(message)<40){
     client.publish('sarim/plant/message','Turning on Pump')
     client.publish('sarim/plant/pump','ON')   
    }
})


