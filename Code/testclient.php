<?php
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
	$result = socket_connect($socket, "localhost", "5555");
	socket_write($socket, "AA", strlen("AA"));
	$result = socket_read($socket, 65536);
	echo "REPLY : ".$result;
	socket_close($socket);
?>
