<?php

$array_ret = json_decode(htmlspecialchars_decode($data, ENT_COMPAT),true);

if($array_ret['isError']){
  print_r($array_ret['errorMessage']);
} else {
  print_r("<a href='../download_pic/downloadlogfile?filePath=".$filepath."'>Click here to download</a><br/><br/>");
  print_r($array_ret['logContent']);
}
?>
