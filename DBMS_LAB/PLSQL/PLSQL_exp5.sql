DECLARE
   num1 NUMBER := &num1;
   num2 NUMBER := &num2;
   operator VARCHAR2(1) := '&operator';
   result NUMBER;
BEGIN
   -- Perform calculation based on the operator
   IF operator = '+' THEN
      result := num1 + num2;
   ELSIF operator = '-' THEN
      result := num1 - num2;
   ELSIF operator = '*' THEN
      result := num1 * num2;
   ELSIF operator = '/' THEN
      result := num1 / num2;
   ELSE
      dbms_output.put_line('Invalid operator');
      result := 0;
   END IF;

   -- Display result
   dbms_output.put_line('Result: ' || result);
END;
/