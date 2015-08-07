<?php
	// Combinaciones de parámetros posibles:
	// 1. action=status
	// Retorna un array en json con el estado de cada id. Ejemplo: {"1":"1","2":"0"}
	//
	// 2. action=status&id=1
	// Retorna el valor del estado para el id 1.
	//
	// 3. action=update&id=1&value=0
	// Actualiza el valor del estado del id 1 poniéndolo en 0.

	$dir = "./data";
	$data_file = $dir . "/data.db";

	if(isset($_GET['action']) && !empty($_GET['action'])) {
    $action = $_GET['action'];
    switch($action) {
    	case 'help':
        	header('Content-Type: text/html; charset=UTF-8');
			echo "Combinaciones de parámetros posibles:<br>";
			echo "1. action=status<br>";
			echo "Retorna un array en json con el estado de cada id. Ejemplo: {\"1\":\"1\",\"2\":\"0\"}.<br><br>";
		
			echo "2. action=status&id=1<br>";
			echo "Retorna el valor del estado para el id 1.<br><br>";
		
			echo "3. action=update&id=1&value=0<br>";
			echo "Actualiza el valor del estado del id 1 poniéndolo en 0.<br>";
        	break;
        case 'status':
        	$data = file_get_contents($data_file);
        	if(isset($_GET['id'])) {
        		$array_data =json_decode($data, true);
        		echo $array_data[$_GET['id']];
        	} else {
	        	echo $data;
        	}
        	break;
    	case 'update': 
    		if(isset($_GET['id']) && isset($_GET['value'])) {
				$data = file_get_contents($data_file);
			
				$array_data =json_decode($data, true);
			
				$array_data[$_GET['id']] = $_GET['value'];
				
				file_put_contents($data_file, json_encode($array_data));
			}
			break;
    	}
    } else {
    	$data = file_get_contents($data_file);
    	$array_data =json_decode($data, true);
    	?>
    	<!DOCTYPE html>
    	<html>
    		<head>
    			<title>Smart Places</title>
				<meta name="viewport" content="width=device-width, initial-scale=1">
    			<link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/jquerymobile/1.4.5/jquery.mobile.min.css" />
				<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
				<script src="http://ajax.googleapis.com/ajax/libs/jquerymobile/1.4.5/jquery.mobile.min.js"></script>
				<script>
					$(document).on("pageinit", function(event) {
						$("#deviceList").on("change", '[name|="switch"]', function(event) {
							$.ajax({
								url: "?action=update&id=" + $(this).attr('id') + "&value=" + $(this).val(),
								success: function() {
								}
							});
						});

						setInterval(function() {
							$.ajax({
								url: "?action=status",
								dataType: "json",
								success: function(data) {
									for(item in data) {
										if($("#"+item).val() != data[item]) {
											$("#"+item).val(data[item]);
											$("#"+item).slider();
											$("#"+item).slider('refresh');
										}
									}
								}
							});
						}, 10000);
					});
				</script>
    		</head>
    		<body>

	    		<div data-role="home">
					<div data-role="header" data-position="fixed">
						<h1>Smart Places</h1>
					</div>

					<div role="main" class="ui-content">
						<ul id="deviceList" data-role="listview">
							<?php foreach($array_data as $key => $val) {
								echo "<li>";
								echo "<label>Device " . $key . "</label>";
								echo "<p class=\"ui-li-aside\" style=\"top: 0px;\">";
								echo "<select name=\"switch-" . $key . "\" id=\"" . $key . "\" data-role=\"slider\">";
								echo "<option value=\"0\"" . ($val==0 ? " selected" : "") . ">Off</option>";
								echo "<option value=\"1\"" . ($val==1 ? " selected" : "") . ">On</option>";
								echo "</select>";
								echo "</p>";
								echo "</li>";
							} ?>
						</ul>
					</div>

					<!--<div data-role="footer" data-position="fixed">
						<h4>Page Footer</h4>
					</div>-->
				</div>

    		</body>
    	</html>
    	<?php
    }
?>