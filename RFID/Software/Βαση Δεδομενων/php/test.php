<?php
echo "Start_________";
foreach($_REQUEST as $key => $value) {
	if($key=="status") {
		$status1 = $value;
	}
}

$con=mysqli_connect("localhost","user123","pass123","test123");
// Check connection
if (!$con) {
  die("Connection error: " . mysqli_connect_errno());
}
echo "<br>status=$status1 <br>";

$query = "UPDATE test321 SET status=$status1 WHERE id=1;";
$result = mysql_query($query) or trigger_error(mysql_error()." in ".$query);
$valid = mysql_num_rows($result);
if($valid){
  echo "$user1, your account is currently verified.";
}

echo "done";

?>