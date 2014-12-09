<style>
table tr td {
	border: 0px;
}
</style>


<?php
global $base_url;
$action = $base_url . '/covidien/device/' . $sno . '?topic=log_viewer';

if(isset($serviceDate) && trim($serviceDate)!=''){
	$current_date = date ( 'm/d/Y', strtotime ( $serviceDate ) );
}
?>

<link rel="stylesheet" type="text/css"
	href="<?php print $base_url?>/sites/all/modules/date/date_popup/themes/datepicker.css">

<script type="text/javascript"
	src="<?php print $base_url?>/sites/all/libraries/jquery.ui/ui/packed/ui.datepicker.packed.js"></script>

<div id="div_search"
	style="text-align: center; width: 100%; border: 0px;">

	<form action="<?php print $action?>" method="get">
		<input type="hidden" name="topic" value="log_viewer" />
		<table>
			<tr>
				<td style="width: 10%;">&nbsp;</td>
				<td style="width: 30%;">Log Type:<input type="text" name="logType"
					value='<?php print $logType;?>' style="width: 150px"></td>
				<td style="width: 30%;">Service Date:<input type="text"
					id="serviceDateDisplay" value='<?php print $current_date?>'
					name="serviceDateDisplay" style="width: 150px"
					onchange="setTime(this.value)"> <input type="hidden"
					id="serviceDate" name="serviceDate"
					value='<?php print $serviceDate;?>' /></td>
				<td style="width: 20%; text-align: left"><input type="submit"
					class="form-submit" value="Go" /></td>
				<td style="width: 10%;">&nbsp;</td>
			</tr>
		</table>
	</form>

</div>

<div id="div_list">
	<table id="tb_result">
	<?php
	$action = $action . "&logType=" . $logType . "&serviceDate=" . $serviceDate;
	if ($sortType == "asc") {
		$desc = true;
		$sortType = "desc";
	} else {
		$sortType = "asc";
		$desc = false;
	}
	?>
		<tr>
			<th class="views-field views-field-field-service-datetime-value"><a
				href="<?php print $action.'&page='.$page.'&sortField=field_service_datetime_value&sortType='.$sortType?>"
				title="sort by Date">Date				
				<?php
				if ($sortField == "field_service_datetime_value") {
					if (! $desc) {
						?>
				<img src="<?php print $base_url?>/misc/arrow-asc.png" alt="sort icon"
					title="sort ascending" width="13" height="13"> 
				<?php }else{?><img src="<?php print $base_url?>/misc/arrow-desc.png"
					alt="sort icon" title="sort descending" width="13" height="13">
				<?php }}?></a></th>
			<th class="views-field views-field-field-service-datetime-value"><a
				href="<?php print $action.'&page='.$page.'&sortField=field_device_log_type_value&sortType='.$sortType?>"
				title="sort by Log Type">Log
				Type
				<?php
				if ($sortField == "field_device_log_type_value") {
					if (! $desc) {
						?>
				<img src="<?php print $base_url?>/misc/arrow-asc.png" alt="sort icon"
					title="sort ascending" width="13" height="13"> 
				<?php }else{?><img src="<?php print $base_url?>/misc/arrow-desc.png"
					alt="sort icon" title="sort descending" width="13" height="13">
				<?php }}?></a></th>
			<th class="views-field views-field-field-service-datetime-value"><a
				href="<?php print $action.'&page='.$page.'&sortField=field_device_log_filename_value&sortType='.$sortType?>"
				title="sort by Log Name">Log
				Name
				<?php
				if ($sortField == "field_device_log_filename_value") {
					if (! $desc) {
						?>
				<img src="<?php print $base_url?>/misc/arrow-asc.png" alt="sort icon"
					title="sort ascending" width="13" height="13"> 
				<?php }else{?><img src="<?php print $base_url?>/misc/arrow-desc.png"
					alt="sort icon" title="sort descending" width="13" height="13">
				<?php }}?></a></th>
		</tr>
			<?php
			if (isset ( $logList ) && count ( $logList ) > 0) {
				$tr_class = "odd";
				$index = 0;
				foreach ( $logList as $log ) {
					$index = $index + 1;
					if ($index % 2 == 0) {
						$tr_class = "even";
					} else {
						$tr_class = "odd";
					}
					?>
				<tr class='<?php print $tr_class?>'>
			<td><?php print date('m/d/Y -H:i:s',strtotime($log->date))?></td>
			<td><?php print $log->log_type?></td>
			<td><a href=""
				onclick="openLogDetails('<?php print $log->log_type?>','<?php print $log->log_filename?>');return false;"><?php print $log->log_filename?></a></td>
		</tr>
			<?php
				}
			} else {
				?>
				<tr>
			<td colspan=3 style="text-align: center">No logs found</td>
		</tr>
			<?php
			}
			?>
</table>
</div>
<div id="div_page">
	<?php
	
	if (isset ( $logList ) && $totalPage > 1) {
		$isFirst = false;
		if ($page == 1) {
			$isFirst = true;
		}
		$isLast = false;
		
		if ($page == $totalPage) {
			$isLast = true;
		}
		
		$firstPage = $page - 4 > 0 ? $page - 4 : 1;
		$lastPage = $page + 4 <= $totalPage ? $page + 4 : $totalPage;
		$previousPage = $page - 1 > 0 ? $page - 1 : 1;
		$nextPage = $page + 1 < $totalPage ? $page + 1 : $totalPage;
		$action = $action . '&sortField=' . $sortField . '&sortType=' . $sortType;
		?>
	<div class="item-list">
		<ul class="pager">
			<?php
		if (! $isFirst) {
			?>
			<li class="pager-first first"><a href="<?php print $action?>"
				title="Go to first page">« first</a></li>
			<li class="pager-previous"><a
				href="<?php print $action.'&page='.$previousPage?>"
				title="Go to previous page">‹ previous</a></li>
			<?php
		}
		for($i = $firstPage; $i <= $lastPage; $i ++) {
			$activeStyle = "";
			if ($i == $page) {
				$activeStyle = "class='active'";
			}
			?>
			<li class="pager-item"><a href="<?php print $action.'&page='.$i?>"
				title="Go to page <?php print $i?>" <?php print $activeStyle?>><?php print $i?></a></li>
			
			<?php
		}
		if (! $isLast) {
			?>
			<li class="pager-next"><a
				href="<?php print $action.'&page='.$nextPage?>"
				title="Go to next page" class="active">next ›</a></li>
			<li class="pager-last last"><a
				href="<?php print $action.'&page='.$totalPage?>"
				title="Go to last page" class="active">last »</a></li>
			<?php
		}
	}
	?>

		</ul>
	</div>
</div>

<script>
	
function openLogDetails(logType,fileName){
	var action='<?php print $base_url?>/covidien/logdetails?type='+logType+'&filename='+fileName;
	window.open (action,'newwindow','height=600,width=1200,top=200,left=400,toolbar=no,menubar=no,scrollbars=yes,resizable=yes,location=no,status=no')	
}

function setTime(time){
	var times=time.split('/');
	if(times.length!=3){
		$("#serviceDate").val('');
		return;
	}
	var month=times[0];
	var date=times[1];
	var year=times[2];
	$("#serviceDate").val(year+"-"+month+"-"+date);
}

	$("#serviceDateDisplay").datepicker({showButtonPanel:true,dateFormat:'mm/dd/yy'});
	$('input').keyup(function(){
		var event = event || window.event;
		if (event.keyCode==13){
			$("form").submit();
		}
	});
</script>
