--creating cursor to find age of each person
DECLARE
  CURSOR c_person IS
    SELECT pid,pname,DOB
    FROM person;
  a_person c_person%ROWTYPE;  --defining a record a_person that corresponds to columns fetched from cursor variable c_person
  today DATE := SYSDATE;
  age NUMBER;
BEGIN
  DBMS_OUTPUT.PUT_LINE('PID     Pname                    DOB          Age');
  DBMS_OUTPUT.PUT_LINE('---     ----------               --------     ----');
  OPEN c_person;
  LOOP
    FETCH c_person INTO a_person;
    EXIT WHEN c_person%NOTFOUND;
    age := trunc(months_between(today, a_person.DOB) / 12);
    DBMS_OUTPUT.PUT_LINE(a_person.pid || '     ' || a_person.pname || '                  ' || a_person.DOB || '    ' || age);
  END LOOP;   
  CLOSE c_person;
END;
/


