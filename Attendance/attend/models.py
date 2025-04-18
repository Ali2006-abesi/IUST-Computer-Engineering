from django.db import models


class StudentName(models.Model):
    Name=models.CharField(max_length=100)
    
class attendance(models.Model):
    student= models.ForeignKey(StudentName, on_delete = models.CASCADE)
    present=models.BooleanField(default=True)
    date=models.DateField()

class exam(models.Model):
    Name = models.CharField(max_length=100)
    Starred = models.BooleanField(default= False)
    Checked=models.BooleanField(default=False)

    def __str__(self):
        return f"{self.Name} - {self.Starred} - {self.Checked}"