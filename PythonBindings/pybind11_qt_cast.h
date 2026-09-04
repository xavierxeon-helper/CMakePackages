#include <pybind11/pybind11.h>
// #include <pybind11/stl.h>

#include <QString>

template <>
struct pybind11::detail::type_caster<QString>
{
public:
   PYBIND11_TYPE_CASTER(QString, _("str"));

   bool load(handle src, bool)
   {

      // Extract PyObject from handle
      PyObject *source = src.ptr();
      if (!PyUnicode_Check(source))
         return false;

      Py_ssize_t size;
      const char *ptr = PyUnicode_AsUTF8AndSize(source, &size);

      if (!ptr)
         return false;

      // Now try to convert into a C++ int
      value = QString::fromUtf8(ptr, size);

      // Ensure return code was OK (to avoid out-of-range errors etc)
      return (!PyErr_Occurred());
   }

   static handle cast(QString src, return_value_policy policy, handle parent)
   {
      return (PyUnicode_FromString(src.toUtf8().data()));
   }
};

template <typename T>
struct pybind11::detail::type_caster<QList<T>>
{
   using Caster = detail::make_caster<T>;

public:
   // Pybind11 required macro
   PYBIND11_TYPE_CASTER(QList<T>, _("QList[") + Caster::name + _("]"));

   // Conversion from Python -> C++
   bool load(handle src, bool)
   {
      sequence seq = reinterpret_borrow<sequence>(src);
      value.clear();
      try
      {
         for (auto item : seq)
         {
            Caster caster;
            if (!caster.load(item, true))
               return false;
            value.append(caster.operator T &&());
         }
         return true;
      }
      catch (...)
      {
         return false;
      }
   }

   // Conversion from C++ -> Python
   static handle cast(const QList<T> &src, return_value_policy policy, handle parent)
   {
      list py_list;
      for (const auto &item : src)
      {
         py_list.append(pybind11::cast(item, policy, parent));
      }
      return py_list.release();
   }
};
