<?php


echo "Start_________";
foreach($_REQUEST as $key => $value) {
	if($key=="status") {
		$status1 = $value;
	}
}


$mysqli = new mysqli("localhost", "user123", "pass123", "test123");

/* check connection */
if ($mysqli->connect_errno) {
    printf("Connect failed: %s\n", $mysqli->connect_error);
    exit();
}

if ($mysqli->query("UPDATE test321 SET status=$status1 WHERE id=1") === TRUE) {
    printf("change done\n");
}


$mysqli->close();
?>
