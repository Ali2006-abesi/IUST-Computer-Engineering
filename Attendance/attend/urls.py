from django.urls import path
from . import views

urlpatterns = [
    path("" ,views.student_list),
    path('attendance/result/<str:date>/' , views.attendance_result , name='attendance_result'),
    path('add/', views.AddStudent),
    path('record' , views.handle_studentadd),
    path("delete/<int:id>" , views.handle_studentdelete ),
]