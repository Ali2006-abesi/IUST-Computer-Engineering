import turtle as t
t.bgcolor("deepskyblue")
t.tracer(0)

def c(n):

    if n <3:
        t.forward(2*n/3)
        
    else :
        
        t.color("green3")
        t.width(5)
        t.forward(n/3)
        t.left(60)
        c(4*n/7)
        t.width(12)
        t.color("green3")
        t.right(120)
        c(4*n/7)
        t.width(5)
        t.color("firebrick4")
        t.left(60)
        t.backward(n/3)
        
def tree():
    t.penup()
    t.setpos(-80,-100)
    t.pendown()    
    c(200)
    t.penup()
    t.setpos(100,-80)
    t.pendown()
    c(300)
    t.penup()
    t.setpos(-200,-80)
    t.pendown()
    c(500)
    t.penup()
    t.setpos(-500,-150)
    t.pendown()
    c(400)
    t.penup()
    t.setpos(450,-90)
    t.pendown()
    c(550)
    t.penup()
    t.setpos(300,-100)
    t.pendown()
    c(200)
    t.penup()
    t.setpos(-280,-260)
    t.pendown()
    c(250)
    t.penup()
    t.setpos(170,-260)
    t.pendown()
    c(250)

def floor():
    t.color("yellowgreen")
    t.fillcolor("yellowgreen")
    t.begin_fill()
    t.penup()
    t.setpos(0,-80)
    t.pendown()
    t.forward(800)
    t.right(90)
    t.forward(500)
    t.right(90)
    t.forward(1600)
    t.right(90)
    t.forward(500)
    t.right(90)
    t.forward(800)
    t.end_fill()
    

def sun(n):
    if n <2:
        return
    else:
        
        t.color("yellow")
        t.width(3)
        t.penup()
        t.setpos(-600,250)
        t.pendown()
        t.forward(70)
        t.right(37)
        sun(3*n/4)
    
def allsun():
    sun(500)
    t.penup()
    t.setpos(-615,210)
    t.pendown()
    t.fillcolor("yellow")
    t.begin_fill()
    t.circle(40)
    t.end_fill()
 
 
def jungle():  
    allsun()
    t.penup()
    t.setpos(0,-80)
    t.pendown()
    t.right(-20)
    floor()
    t.left(90)
    tree()
    t.hideturtle()
    
jungle()

t.update()

t.mainloop()