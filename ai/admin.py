from django.contrib import admin
from .models import  Binary_Tree_Model_v1

# Register your models here.
@admin.register(Binary_Tree_Model_v1)
class Binary_Tree_Model_v1_admin(admin.ModelAdmin):
    list_display = ("id", "x", "y", "result", "created_at")
    search_fields = ("result",)
    list_filter = ("result", "created_at")
    ordering = ("-created_at",)

    fields = ("x", "y", "result")
    readonly_fields = ("result",)