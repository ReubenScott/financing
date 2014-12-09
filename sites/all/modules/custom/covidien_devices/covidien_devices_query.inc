<?php

/**
 * Query functions
 */

function autoSuggestionDeviceQuery($string, $arg1, $devices_nid, $name, $uid) {
  $where = '';
  $matches = array();
  $qry_arg = array();
  $qry_arg[] = $string;
  if ($arg1 != 'All') {
    $where = " and T3.field_device_type_nid ='%s'";
    $qry_arg[] = $arg1;
  }
  else {
    if ($uid != 1) {
      $where = " and T3.field_device_type_nid IN (%s) ";
      $qry_arg[] = $devices_nid;
    }
  }
  $covidien_user = checkifCovidienUserQuery($name);
  if ($covidien_user == 'No') {
    $customer_name = getCompanyinfoQuery($name);
    $customer_query = ' and T2.field_device_owner_nid IN (%s)';
    $qry_arg[] = $customer_name;
  }
  $query = "select T2.field_device_serial_number_value from node as T1 join content_type_device as T2 on T1.nid = T2.nid join content_field_device_type as T3 on T1.nid = T3.nid where T2.field_device_serial_number_value LIKE '%%%s%%' $where $customer_query limit 0,20";
  $result = db_query($query, $qry_arg);
  return $result;
}

function checkifCovidienUserQuery($name) {
  $query = "Select T2.field_covidien_employee_value from {node} as T1 join {content_type_person} as T2 on T1.nid = T2.nid where T1.title = '%s' and T1.type='person'";
  return db_result(db_query($query, $name));
}

function getCompanyinfoQuery($name) {
  $query = "Select T2.field_company_name_nid from {node} as T1 join {content_type_person} as T2 on T1.nid = T2.nid where T1.title = '%s' and T1.type='person'";
  return db_result(db_query($query, $name));
}

function getBuCustomerinfoQuery($company_nid) {
  $query = "select nid from {content_type_bu_customer} where field_customer_party_pk_nid = '%s'";
  return db_query($query, $company_nid);
}

function getFacilitynidQuery($nid) {
  $query = "select nid from {content_type_customer_facility} where field_customer_pk_nid = '%s'";
  return db_result(db_query($query, $nid));
}

function getFacilityinfoQuery($fid) {
  $query = "select field_facility_pk_nid from {content_field_facility_pk} where nid = '%s'";
  return db_result(db_query($query, $fid));
}

function getConfiginfoQuery($id) {
  $query = "Select node.title from {content_type_device} as DEVICE join {content_type_device_type_config} as CONFIG on DEVICE.field_device_type_config_nid = CONFIG.nid join {node} on node.nid = CONFIG.nid and node.vid = CONFIG.vid where DEVICE.field_device_serial_number_value = '%s'";
  return db_result(db_query($query, $id));
}

function getLocationnidQuery($id) {
  $query = "Select T1.field_location_id_nid from {content_type_device_installation} as T1 join {content_field_device_pk} as T2 on T1.nid = T2.nid join {content_type_device} as T3 on T2.field_device_pk_nid = T3.nid where T3.field_device_serial_number_value = '%s'";
  return db_result(db_query($query, $id));
}

function getCountryinfoQuery($id) {
  $query = "select T4.title from {content_type_device_installation} as T1 join {content_field_device_pk} as T2 on T1.nid = T2.nid join {content_type_device} as T3 on T2.field_device_pk_nid = T3.nid join {node} as T4 on T1.field_device_country_nid = T4.nid where T3.field_device_serial_number_value='%s'";
  return db_result(db_query($query, $id));
}

function getDeviceownerinfoQuery($id) {
  $query = "select T1.field_device_owner_nid,T2.field_device_type_nid as nid,T1.field_maintance_expiration_date_value from {content_type_device} as T1 inner join {content_field_device_type} as T2 where T1.nid = T2.nid and T1.field_device_serial_number_value= '%s'";
  return db_query($query, $id);
}

function getRegionInfo($cid) {
  $query = "select nid,field_bu_customer_account_number_value from content_type_bu_customer where field_customer_party_pk_nid = '%s'";
  return db_query($query, $cid);
}

function getAssociatedHardwaresQuery() {
 $query = "SELECT node.nid AS nid, node.title AS node_title, node_node_data_field_device_component.title AS node_node_data_field_device_component_title, node_node_data_field_device_component.nid AS node_node_data_field_device_component_nid, node.type AS node_type, node_node_data_field_device_component.type AS node_node_data_field_device_component_type, node_node_data_field_component_device_node_data_field_device_serial_number.field_device_serial_number_value AS node_node_data_field_component_device_node_data_field_device_serial_number_field_device_serial_number_value, node_node_data_field_component_device.nid AS node_node_data_field_component_device_nid, node_node_data_field_component_device.type AS node_node_data_field_component_device_type, node_node_data_field_component_device.vid AS node_node_data_field_component_device_vid, node_node_data_field_device_component_node_data_field_hw_version.field_hw_version_value AS node_node_data_field_device_component_node_data_field_hw_version_field_hw_version_value, node_node_data_field_device_component.vid AS node_node_data_field_device_component_vid, node_node_data_field_device_component_node_data_field_hw_version.field_hw_description_value AS node_node_data_field_device_component_node_data_field_hw_version_field_hw_description_value, node_data_field_expiration_datetime.field_expiration_datetime_value AS node_data_field_expiration_datetime_field_expiration_datetime_value, node.vid AS node_vid FROM node node  LEFT JOIN {content_type_device_component_history} node_data_field_device_component ON node.vid = node_data_field_device_component.vid LEFT JOIN {node} node_node_data_field_device_component ON node_data_field_device_component.field_device_component_nid = node_node_data_field_device_component.nid LEFT JOIN {content_type_device_component_history} node_data_field_component_device ON node.vid = node_data_field_component_device.vid LEFT JOIN {node} node_node_data_field_component_device ON node_data_field_component_device.field_component_device_nid = node_node_data_field_component_device.nid LEFT JOIN {content_field_expiration_datetime} node_data_field_expiration_datetime ON node.vid = node_data_field_expiration_datetime.vid LEFT JOIN {content_type_device} node_node_data_field_component_device_node_data_field_device_serial_number ON node_node_data_field_component_device.vid = node_node_data_field_component_device_node_data_field_device_serial_number.vid LEFT JOIN {content_field_expiration_datetime} device_expiration_datetime on device_expiration_datetime.vid = node_node_data_field_component_device_node_data_field_device_serial_number.vid LEFT JOIN {content_type_hardware }node_node_data_field_device_component_node_data_field_hw_version ON node_node_data_field_device_component.vid = node_node_data_field_device_component_node_data_field_hw_version.vid JOIN {content_field_expiration_datetime} expiry on expiry.vid = node_node_data_field_device_component_node_data_field_hw_version.vid and expiry.field_expiration_datetime_value IS NULL WHERE ((node.type in ('device_component_history')) AND (node_node_data_field_device_component.type in ('hardware')) AND (node_node_data_field_component_device_node_data_field_device_serial_number.field_device_serial_number_value = '%s')) AND ((node_data_field_expiration_datetime.field_expiration_datetime_value IS NULL) AND (device_expiration_datetime.field_expiration_datetime_value IS NULL)) ORDER BY node_node_data_field_component_device_node_data_field_device_serial_number_field_device_serial_number_value ASC";
 return $query;
}

/**
 * Return Query object to select Software associated to Device serial number($var)
 */
function getSWquery($var) {
  $query = db_query("SELECT node.nid AS nid,node.title AS node_title, node_node_data_field_device_component.title AS node_node_data_field_device_component_title, node_node_data_field_device_component.nid AS node_node_data_field_device_component_nid, node.type AS node_type, node_node_data_field_device_component.type AS node_node_data_field_device_component_type, node_node_data_field_component_device_node_data_field_device_serial_number.field_device_serial_number_value AS node_node_data_field_component_device_node_data_field_device_serial_number_field_device_serial_number_value, node_node_data_field_component_device.nid AS node_node_data_field_component_device_nid, node_node_data_field_component_device.type AS node_node_data_field_component_device_type, node_node_data_field_component_device.vid AS node_node_data_field_component_device_vid, node_node_data_field_device_component_node_data_field_sw_version.field_sw_version_value AS node_node_data_field_device_component_node_data_field_sw_version_field_sw_version_value, node_node_data_field_device_component.vid AS node_node_data_field_device_component_vid, node_node_data_field_device_component_node_data_field_sw_version.field_sw_description_value AS node_node_data_field_device_component_node_data_field_sw_version_field_sw_description_value, node_node_data_field_update_to_component_node_data_field_sw_version.field_sw_version_value AS node_node_data_field_update_to_component_node_data_field_sw_version_field_sw_version_value, node_node_data_field_update_to_component.nid AS node_node_data_field_update_to_component_nid, node_node_data_field_update_to_component.type AS node_node_data_field_update_to_component_type, node_node_data_field_update_to_component.vid AS node_node_data_field_update_to_component_vid, node_node_data_field_hw_list.title AS node_node_data_field_hw_list_title, node_node_data_field_hw_list.nid AS node_node_data_field_hw_list_nid FROM {node} node  LEFT JOIN {content_type_device_component_history} node_data_field_device_component ON node.vid = node_data_field_device_component.vid LEFT JOIN {node} node_node_data_field_device_component ON node_data_field_device_component.field_device_component_nid = node_node_data_field_device_component.nid LEFT JOIN {content_type_device_component_history} node_data_field_component_device ON node.vid = node_data_field_component_device.vid LEFT JOIN {node} node_node_data_field_component_device ON node_data_field_component_device.field_component_device_nid = node_node_data_field_component_device.nid LEFT JOIN {content_type_device_component_history} node_data_field_update_to_component ON node.vid = node_data_field_update_to_component.vid LEFT JOIN {node} node_node_data_field_update_to_component ON node_data_field_update_to_component.field_update_to_component_nid = node_node_data_field_update_to_component.nid LEFT JOIN {content_field_hw_list} node_node_data_field_device_component_node_data_field_hw_list ON node_node_data_field_device_component.vid = node_node_data_field_device_component_node_data_field_hw_list.vid LEFT JOIN {node} node_node_data_field_hw_list ON node_node_data_field_device_component_node_data_field_hw_list.field_hw_list_nid = node_node_data_field_hw_list.nid LEFT JOIN {content_field_expiration_datetime} node_data_field_expiration_datetime ON node.vid = node_data_field_expiration_datetime.vid LEFT JOIN {content_type_device} node_node_data_field_component_device_node_data_field_device_serial_number ON node_node_data_field_component_device.vid = node_node_data_field_component_device_node_data_field_device_serial_number.vid LEFT JOIN {content_field_expiration_datetime} as device_expiration_datetime on device_expiration_datetime.nid = node_node_data_field_component_device_node_data_field_device_serial_number.nid LEFT JOIN {content_type_software} node_node_data_field_device_component_node_data_field_sw_version ON node_node_data_field_device_component.vid = node_node_data_field_device_component_node_data_field_sw_version.vid JOIN {content_field_expiration_datetime} expiry on expiry.vid = node_node_data_field_device_component_node_data_field_sw_version.vid and expiry.field_expiration_datetime_value IS NULL LEFT JOIN {content_type_software} node_node_data_field_update_to_component_node_data_field_sw_version ON node_node_data_field_update_to_component.vid = node_node_data_field_update_to_component_node_data_field_sw_version.vid WHERE ((node.type in ('device_component_history')) AND (node_node_data_field_device_component.type in ('software')) AND (node_node_data_field_component_device_node_data_field_device_serial_number.field_device_serial_number_value = '$var')) AND ((node_data_field_expiration_datetime.field_expiration_datetime_value IS NULL) AND (device_expiration_datetime.field_expiration_datetime_value IS NULL)) ORDER BY node_node_data_field_component_device_node_data_field_device_serial_number_field_device_serial_number_value ASC");
  return $query;
}

function getDeviceInfoQuery($installation_nid) {
  $query = "select T3.nid as device_nid,T3.field_device_serial_number_value as serial_number,T4.title as customer_name,device_node.title as device_type from {node} as node join {content_type_device_installation} as T1 on node.vid = T1.vid join {content_field_device_pk} as content_field_device_pk on T1.nid = content_field_device_pk.nid join {node} as T2 on content_field_device_pk.field_device_pk_nid = T2.nid join {content_type_device} as T3 on T2.vid = T3.vid join {node} as T4 on T3.field_device_owner_nid = T4.nid join {content_field_device_type} as T6 on T3.vid = T6.vid join {node} as {device_node} on T6.field_device_type_nid = device_node.nid where T1.nid = '%s'";
  return db_query($query, $installation_nid);
}
function getFromcompHistory($from_sw, $device_nid) {
  $query = 'select nid from {content_type_device_component_history} where field_device_component_nid = "%s" and field_component_device_nid = "%s"';
  return db_result(db_query($query, $from_sw, $device_nid));
}

function getSWcompNidQuery($from_sw, $installation_nid) {
  $query = "select field_to_device_component_nid from content_type_device_service_history where field_from_device_component_nid = '%s' and field_device_installation_pk_nid = '%s' and field_upgrade_status_value='installed'";
  return db_result(db_query($query, $from_sw, $installation_nid));
}

function getToSWfromLogQuery($service_id, $from_sw) {
  $query = 'select field_to_component_nid_value from {content_type_device_component_upgrade_log} where field_uh_device_service_history_value = "%s" and field_from_component_nid_value = "%s"';
  return db_result(db_query($query, $service_id, $from_sw));
}

function getToSWfromLogQuerynoservice($next_component_nid, $installation_nid) {
  $query = 'select field_component_history_nid_value from {content_type_device_component_upgrade_log} where field_component_history_nid_value = "%s" and field_uh_device_installation_pk_value = "%s"';
  return db_result(db_query($query, $next_component_nid, $installation_nid));
}

function getServicewithcompQuery($from_sw, $installation_nid) {
  $query = "select T3.title as Person,T2.field_service_datetime_value as date from {node} as node join {content_type_device_service_history} as T2 on node.vid = T2.vid join {node} as T3 on T2.field_service_person_pk_nid = T3.nid where T2.field_from_device_component_nid = '%s' and T2.field_device_installation_pk_nid = '%s'";
  return db_query($query, $from_sw, $installation_nid);
}

function getServicehistoryinfoQuery($service_id) {
  $query = "select T3.title as Person,T2.field_service_datetime_value as date from {node} as node join {content_type_device_service_history} as T2 on node.vid = T2.vid join {node} as T3 on T2.field_service_person_pk_nid = T3.nid where node.nid = '%s'";
  return db_query($query, $service_id);
}

function getUpgradeloginfo($service_nid) {
  $query = "select * from {content_type_device_component_upgrade_log} where field_uh_device_service_history_value = '%s'";
  return db_query($query, $service_nid);
}

function getUpgradeloginfonoserviceid($from_component_nid) {
  $query = "select * from {content_type_device_component_upgrade_log} where field_component_history_nid_value = '%s'";
  return db_query($query, $from_component_nid);
}

function getCurrentConfigQuery($serial_number) {
  $query = "select T1.field_device_component_nid,T1.field_update_to_component_nid from {node} as history_node join {content_type_device_component_history} as T1 on T1.vid = history_node.vid join {content_type_device} as T2 on T2.nid = T1.field_component_device_nid join {node} as device_node on device_node.vid = T2.vid join {content_field_expiration_datetime} as expire on expire.vid = T1.vid where T2.field_device_serial_number_value = '%s' and expire.field_expiration_datetime_value is NULL";
  return db_query($query, $serial_number);
}

function getservicenidupgradelog($installation_nid, $from, $service_nid) {
  $query = "select count(*) as total from {content_type_device_component_upgrade_log} where field_uh_device_installation_pk_value = '%s' and field_uh_device_service_history_value = '%s'";
  return db_result(db_query($query, $installation_nid, $service_nid));
}

function autoSuggestionAccountDeviceQuery($string, $value, $customer_nid_arr, $covidien_user) {
  $where = '';
  $matches = array();
  $qry_arg = array();
  $where = '';
  if (!empty($value) && $value != 'all') {
    $where = ' node1.title="%s" and';
    $qry_arg[] = $value;
  }

  $tmpwhere='';
  if ($covidien_user != 'Yes') {
    $customer_nid = implode(',', $customer_nid_arr);
    $tmpwhere = " node1.nid IN (%s) AND ";
    $qry_arg[] = $customer_nid;
  }
  $qry_arg[] = $string;

  $query = "SELECT content_type_bu_customer.field_bu_customer_account_number_value FROM {content_type_party} as content_type_party JOIN {content_type_bu_customer} as content_type_bu_customer ON content_type_bu_customer.field_customer_party_pk_nid=content_type_party.nid JOIN {node} as account_node ON account_node.vid = content_type_bu_customer.vid JOIN {node} as node1 ON node1.nid=content_type_bu_customer.field_customer_party_pk_nid JOIN {content_field_expiration_datetime} as expiry ON expiry.vid = content_type_bu_customer.vid AND expiry.field_expiration_datetime_value is NULL WHERE $where $tmpwhere content_type_bu_customer.field_bu_customer_account_number_value LIKE '%%%s%%' limit 0,20";
  $result = db_query($query, $qry_arg);
  return $result;
}

function autoSuggestionCompanyDeviceQuery($string, $value, $customer_nid_arr, $covidien_user) {
  $where = '';
  $matches = array();
  $qry_arg = array();
  $tmpwhere='';
  $where = '';
  if (!empty($value) && $value != 'all') {
    $where = ' content_type_bu_customer.field_bu_customer_account_number_value="%s" and';
    $qry_arg[] = $value;
  }
  if ($covidien_user != 'Yes') {
    $customer_nid = implode(',', $customer_nid_arr);
    $tmpwhere = " node1.nid IN (%s) AND ";
    $qry_arg[] = $customer_nid;
  }
  $qry_arg[] = $string;
 
  $query = "SELECT " .
  "node1.title as customername " .
  "FROM {content_type_party} " .
	"JOIN {content_field_expiration_datetime} as expiry_party ON expiry_party.vid = content_type_party.vid and expiry_party.field_expiration_datetime_value is NULL " .
  "JOIN {content_type_bu_customer} on " .
  "content_type_bu_customer.field_customer_party_pk_nid=content_type_party.nid " .
  "JOIN {node} as node1 on " .
  "node1.nid=content_type_bu_customer.field_customer_party_pk_nid " .
  "WHERE $where $tmpwhere " .
  "node1.title like '%%%s%%' limit 0,20";
  $result = db_query($query, $qry_arg);
  return $result;
}