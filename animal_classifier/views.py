from django.shortcuts import render, redirect
from ai.forms import Binary_Tree_Model_v1_form
from ai.models import Binary_Tree_Model_v1
from django.contrib import messages


def main_view(request):
    if request.method == 'POST':
        form = Binary_Tree_Model_v1_form(request.POST)
        if form.is_valid():
            form.save()
            obj = Binary_Tree_Model_v1.objects.latest('id')
            result = obj.give_result()
            form = Binary_Tree_Model_v1_form()
            messages.success(request,'Thanks!')
            return render(request,'main.html',{'result':result,'form': form})
    else:
        form = Binary_Tree_Model_v1_form()
    return render(request, 'main.html', {'form': form})

