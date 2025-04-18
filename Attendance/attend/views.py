from django.shortcuts import render , redirect ,get_object_or_404
from .models import StudentName,attendance
from django.utils import timezone

def AddStudent(request):
    return render(request , 'add_student.html')
def handle_studentadd(request):
    if request.method=="POST":
        new_student= StudentName(Name=request.POST["name"])
        new_student.save()
        
    return redirect("/")
def student_list(request):
    students=StudentName.objects.all()
    if request.method=="POST":
        date=request.POST.get('date' ,str(timezone.now().date()))
        
        for student in students:
            present = request.POST.get(f'present_{student.id}', 'off') == 'on'
            absent = request.POST.get(f'absent_{student.id}', 'off') == 'on'
            if present and not absent:
                attendance.objects.update_or_create(student=student, date=date, defaults={'present': True})
            elif absent and not present:
                attendance.objects.update_or_create(student=student, date=date, defaults={'present': False})

        return redirect("attendance_result" , date=date)
    return render(request, 'student_list.html', {'students': students})

def attendance_result(request , date):
    attendance_save=attendance.objects.filter(date=date)
    return render(request , 'attendance_result.html', {'attendance_records': attendance_save, 'date':date})

def handle_studentdelete(request,id):
    student=StudentName.objects.get(id=id)
    student.delete()
    return redirect("/")