# Generated by Django 5.1.4 on 2025-01-05 17:16

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('attend', '0004_delete_exam'),
    ]

    operations = [
        migrations.CreateModel(
            name='exam',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('Name', models.CharField(max_length=100)),
                ('Starred', models.BooleanField(default=False)),
                ('Checked', models.BooleanField(default=False)),
            ],
        ),
    ]
