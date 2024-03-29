# Tester670

74LS670 / 74HCT670 Tester

This is a chip tester for the 74x670 High-Speed CMOS Logic 4x4 Register. For example the CD54HC670, CD74HC670, CD74HCT670 chips.

![](images/IMG_20220116_184934126.jpg)

## Wiring diagram

<table border="0">
 <tr>
    <td><b style="font-size:30px"></b></td>
    <td><b style="font-size:30px"></b></td>
 </tr>
 <tr>
    <td>
<pre>
Arduino Pin   74LS670 Pin

A1 ---------- 15/D0 (input/write)
A3 ---------- 1/D1
A2 ---------- 2/D2
A0 ---------- 3/D3
D6 ---------- 10/Q0 (output/read)
D7 ---------- 9/Q1
D8 ---------- 7/Q2
D9 ---------- 6/Q3
D2 ---------- 14/Write Sel A
D3 ---------- 13/Write Sel B
D10 --------- 5/Read Sel A
D12 --------- 4/Read Sel B
D4 ---------- 12/Write Enable #
D5 ---------- 11/Read Enable #
</pre>
</td>
<td>

![](images/74x670-pinout.jpg)

</td>
</tr>
</table>


Successful testing result at Arduino Serial Debug Window :

<pre>
Tester_670 v0.1

PHASE 1

........

PHASE 2

................................................................

Completed
</pre>


You can find some pictures at my blog (korean) :

https://blog.naver.com/cloudree/221696084596

Thanks
