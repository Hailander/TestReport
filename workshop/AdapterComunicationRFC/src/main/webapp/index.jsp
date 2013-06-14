<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
		<center><div style="width: 300px; border: 2px solid blue;">
		<div style="background: green; color:white; size"><center>RFC</div>
	<form>
			<br>
					<br/>
			<label>Enter your RFC:</label>
				<input type="text" placeholder="type your RFC" maxlength="15"/>
					<br>
					<br/>
						<label>Operation:</label>
							<select name="transporte">
								<option value="pay">Payment</option>
								<option value="loan">Get a new loan</option>
								<option value="close">Close loan</option>
							</select>
							<br>
							<br>
							<br>
								<input type=submit value="SUBMIT"/>
								
		
	</form>
	</div>
</body>
</html>