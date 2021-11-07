const net = require('net');
const port = 7070;
const host = '192.168.1.2';

const server = net.createServer();

server.listen(port, host, () => {
	console.log('TCP Server is running on port ' + port +'.');
});

server.on('connection', sock => {
	console.log('CONNECTED: ' + sock.remoteAddress + ':' + sock.remotePort);

	sock.on('data', data => {
		console.log('DATA ' + sock.remoteAddress + ': ' + data);
	});

	sock.on('close', data => {
		console.log('CLOSED: ' + data);
	});
});



