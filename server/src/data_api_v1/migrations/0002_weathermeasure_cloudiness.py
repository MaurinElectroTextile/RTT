# Generated by Django 2.1.3 on 2018-11-14 14:33

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('data_api_v1', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='weathermeasure',
            name='cloudiness',
            field=models.DecimalField(decimal_places=2, default=0.0, max_digits=5, verbose_name='cloudiness'),
        ),
    ]
