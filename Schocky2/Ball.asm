        PUBLIC _BALL
        PUBLIC _BALL_TOT


_BALL:
        db      @00111100
        db      @01111110
        db      @11111111
        db      @11111111
        db      @11111111
        db      @11111111
        db      @01111110
        db      @00111100
         
        db      @00000000   
        db      @00000000   
        db      @00000000   
        db      @00000000   
        db      @00000000   
        db      @00000000   
        db      @00000000   
        db      @00000000   

; 1 rechts
        db      @00011110
        db      @00111111
        db      @01111111
        db      @01111111
        db      @01111111
        db      @01111111
        db      @00111111
        db      @00011110
        
        db      @00000000   
        db      @00000000   
        db      @10000000   
        db      @10000000   
        db      @10000000   
        db      @10000000   
        db      @00000000   
        db      @00000000   
; 2 rechts
        db      @00001111
        db      @00011111
        db      @00111111
        db      @00111111
        db      @00111111
        db      @00111111
        db      @00011111
        db      @00001111
        
        db      @00000000
        db      @10000000
        db      @11000000
        db      @11000000
        db      @11000000
        db      @11000000
        db      @10000000
        db      @00000000
        
; 3 rechts
        db      @00000111
        db      @00001111
        db      @00011111
        db      @00011111
        db      @00011111
        db      @00011111
        db      @00001111
        db      @00000111
        
        db      @10000000
        db      @11000000
        db      @11100000
        db      @11100000
        db      @11100000
        db      @11100000
        db      @11000000
        db      @10000000
        
; 4 rechts
        db      @00000011
        db      @00000111
        db      @00001111
        db      @00001111
        db      @00001111
        db      @00001111
        db      @00000111
        db      @00000011
        
        db      @11000000
        db      @11100000
        db      @11110000
        db      @11110000
        db      @11110000
        db      @11110000
        db      @11100000
        db      @11000000
        
; 5 rechts
        db      @00000001
        db      @00000011
        db      @00000111
        db      @00000111
        db      @00000111
        db      @00000111
        db      @00000011
        db      @00000001
        
        db      @11100000
        db      @11110000
        db      @11111000
        db      @11111000
        db      @11111000
        db      @11111000
        db      @11110000
        db      @11100000
        
; 6 rechts
        db      @00000000
        db      @00000001
        db      @00000011
        db      @00000011
        db      @00000011
        db      @00000011
        db      @00000001
        db      @00000000
        
        db      @11110000
        db      @11111000
        db      @11111100
        db      @11111100
        db      @11111100
        db      @11111100
        db      @11111000
        db      @11110000
        
; 7 rechts
        db      @00000000
        db      @00000000
        db      @00000001
        db      @00000001
        db      @00000001
        db      @00000001
        db      @00000000
        db      @00000000
        
        db      @01111000
        db      @11111100
        db      @11111110
        db      @11111110
        db      @11111110
        db      @11111110
        db      @11111100
        db      @01111000
        
._BALL_TOT
.BALL1          DB      03FH,07EH,0FDH,0DFH,0FFH,0F7H,07EH,01CH
.BALL2          DB      030H,07CH,0FDH,05FH,0F7H,0F7H,05FH,01CH
.BALL3          DB      034H,074H,0FCH,05FH,077H,0F3H,01EH,09CH
.BALL4          DB      034H,064H,0FEH,01BH,06EH,0F6H,033H,00DH
.BALL5          DB      034H,066H,0DDH,024H,063H,0CAH,060H,019H
.BALL6          DB      010H,064H,001H,010H,053H,040H,018H,0
.BALL7          DB      0,40H,4,0,20H,0,1,20H
.BALL8          DB      0,0,0,0,0,0,0,0
        
