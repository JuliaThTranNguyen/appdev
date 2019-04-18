<?php
$log_file = 'sound.txt';
$email=$_POST['email'];
$id=$_POST['id'];
$values= $_POST['db'];
//echo "Vaasa timezone is used\n";
//date_default_timezone_set("UTC");//this line is not necessary if you just only want to use the local time
$str = date("M d Y H:i:s",time()).' '.$values.' ' .$email.' '.$id."\n";
//echo "This is from the server.\n";
//now we open the file
if(file_exists($log_file)){
	$fp=fopen($log_file,a);//the file is open as append mode
	fwrite($fp,$str);
	fclose($fp);
}
else {
	//the file doesn't exists, so open a new one
	$fp = fopen($log_file,w);
	fwrite($fp,$str);
	fclose($fp);
	
}
?>
