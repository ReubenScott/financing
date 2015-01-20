<?php

/**
 * @file
 * Implements security policy functionality.
 */


/**
 * Helper function for filter xss
 */
function filter_xss_arr($arg = array()) {
  $retarg = array();
  if (is_array($arg)) {
    if (count($arg) > 0) {
      foreach ($arg as $key => $val) {
        if (!is_array($val)) {
          $retarg[$key] = check_plain($val);
        } else {
          $retarg[$key] = filter_xss_arr($val);
        }
      }
    }
  } else {
    return check_plain($arg);
  }
  return $retarg;
}



/**
 *  加密:echo encrypt( '你好，美女！','password');  
 *
 * @param unknown_type $key
 * @param unknown_type $string
 * @param unknown_type $decrypt
 * @return unknown
 */
function encrypt($string, $key='mysecretkey'){
  $encrypted = '';
  for($i=0;$i<strlen($string);$i++){
    $sChar    = substr($string, $i, 1);
    $keyChar = substr($key, ($i % strlen($key)) - 1, 1);
    $sChar    = chr(ord($sChar) + ord($keyChar));
    $encrypted .= $sChar;
  }
  return base64_encode($encrypted);
}

/**
 * 解密:echo decrypt('XSoZWAogYSEAUiMHUh4mVB/z','password');
 *
 * @param unknown_type $string
 * @param unknown_type $key
 * @return unknown
 */
function decrypt($string, $key='mysecretkey'){
  $decrypted = '';
  $string   = base64_decode($string);
  for($i=0;$i<strlen($string);$i++){
    $sChar    = substr($string, $i, 1);
    $keyChar = substr($key, ($i % strlen($key)) - 1, 1);
    $sChar    = chr(ord($sChar) - ord($keyChar));
    $decrypted .= $sChar;
  }
  return $decrypted;
}





