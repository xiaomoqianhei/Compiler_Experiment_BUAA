var
	stack: array[1000] of integer;
	base: integer;
	MaxLen : integer;
	readnum : integer;
	i : integer;
	temp : char;
function IsEmpty : integer;
begin
	if base = 0 then
		IsEmpty := 1
	else
		IsEmpty := 0
end;
function IsFull : integer;
begin
	if base = MaxLen then
		IsFull := 1
	else
		IsFull := 0
end;
procedure MakeEmpty;
begin
	base := 0
end;
procedure Pop;
begin
	if IsEmpty = 1 then
		write ("Stack is Empty")
	else 
		base := base - 1
end;
function Top : integer;
begin
	if IsEmpty = 1 then
		write ("Stack is Empty")
	else
		Top := stack[base-1]
end;
procedure Push (X : integer);
begin
	if IsFull = 1 then
		write ("Stack is Full")
	else begin
			stack[base] := X; 
			base := base + 1
	end
end;
procedure PopN(popNum : integer);
begin
	write (Top);
	if popNum >= 1 then
		begin
		Pop;
		PopN(popNum - 1)
	end
end;
begin
	read (MaxLen);
	MakeEmpty;
	for i := 1 to 0 do              
	begin
		read (temp);
		if temp = 1 then begin
			read (temp) ;
			Push (temp) 
		end
		else if temp = 2 then
			Pop
		else if temp = 0 then       
			i := 0
	end;
	PopN(base)
end.
