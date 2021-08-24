<?php


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


/* Select queries return a resultset */
if ($result = $mysqli->query("SELECT status FROM test321 LIMIT 10")) {
    printf("Status=");
    $row = $result->fetch_assoc();
    printf("%d",$row[status]);
    /* free result set */
    $result->close();
}

/* If we have to retrieve large amount of data we use MYSQLI_USE_RESULT */
if ($result = $mysqli->query("SELECT * FROM City", MYSQLI_USE_RESULT)) {

    /* Note, that we can't execute any functions which interact with the
       server until result set was closed. All calls will return an
       'out of sync' error */
    if (!$mysqli->query("SET @a:='this will not work'")) {
        printf("Error: %s\n", $mysqli->error);
    }
    $result->close();
}

$mysqli->close();
?>