const express = require('express');
const socketIo= require('socket.io');
const SerialPort = require('serialport');
const htpp=require('http');
const path = require('path');


const app = express();

const server=htpp.createServer(app);
const io= socketIo.listen(server);



const ReadLine= SerialPort.parsers.Readline;



const mySerial =new SerialPort('COM5',{
    baudRate:9600
});
const parser = mySerial.pipe(new ReadLine({ delimiter: '\r\n'}));

io.on('connection', function(socket){
    console.log('nuevo socket connectado');
    
});

app.get('/',(req,res,next)=>{

    res.sendFile(__dirname + '/index.html')
    
});

app.use( express.static( path.join(__dirname , 'public')));
//app.use( express.static(path.join(__dirname , 'fonts')));
//app.use( express.static(path.join(__dirname , 'images')));
//app.use( express.static(path.join(__dirname , 'js')));
//app.use( express.static(path.join(__dirname , 'scss')));

parser.on('open', function(){
    console.log("se abrio el puerto serial");
    
});

//datos de humedad
parser.on('data', function(data) {
    
    

    console.log(data.toString().substr(0,5) +","+ data.toString().substr(5,5)+"," + data.toString().substr(10,1)+","+ data.toString().substr(11));
    //console.log(data.toString());
    io.emit('arduino:data', {
        
        value: data.toString().substr(0,5)
    });
    

});

//datos de temperatura
parser.on('data', function(data) {
    
    

    
    io.emit('arduino:data1', {
        
        value: data.toString().substr(5,5)
    });
    

});

mySerial.on('err', function() {
    console.log(err.message);
    
});
//tamaño de la planta

parser.on('data', function(data) {
    
    

    
    io.emit('arduino:data2', {
        
        value: (data.toString().substr(10,1)) 
    });
    

});




//humeda de la tierra

parser.on('data', function(data) {
    
    

    
    io.emit('arduino:data3', {
        
        value: data.toString().substr(11)
    });
    

});





server.listen(3000, () =>{
    console.log( 'se inicializo el server port : 3000');
    
});


//parte manual



mySerial.on('open',function() {
    console.log('Serial Port ' + ' is opened.');
   
  });


app.post('/clicked',(req,res,next)=>{

    
    mySerial.write("re3-OFF\n")
    
});

app.post('/clicked1',(req,res,next)=>{

    mySerial.write("re3-ON\n")
    
});

app.post('/clicked2',(req,res,next)=>{

    
    mySerial.write("re5-OFF\n");
    mySerial.write("re6-OFF\n");
    mySerial.write("re4-OFF\n");
    mySerial.write("re1-ON\n");
    mySerial.write("re2-OFF\n");
    
});

app.post('/clicked3',(req,res,next)=>{

    
    mySerial.write("re5-ON\n");
    mySerial.write("re6-ON\n");
    mySerial.write("re1-ON\n");
    mySerial.write("re2-ON\n");
    mySerial.write("re4-ON\n");
    
});

app.post('/clicked4',(req,res,next)=>{

  

    mySerial.write("re5-ON\n");
    mySerial.write("re6-ON\n");
    mySerial.write("re1-ON\n");
    mySerial.write("re2-ON\n");
    mySerial.write("re4-ON\n");
    mySerial.write("re1-OFF\n");
    
    
});


app.post('/clicked5',(req,res,next)=>{

   

    mySerial.write("re1-ON\n");
    mySerial.write("re2-ON\n");
    
});

app.post('/clicked6',(req,res,next)=>{
    mySerial.write("pgl\n");
       
});