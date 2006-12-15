#include <Python.h>
#include <pygobject.h>
#include <stdarg.h>
#include "gcompris/gcompris.h"
#include "py-mod-sound.h"
#include "py-gcompris-board.h"

/* All functions provided by this python module
 * wraps a gcompris function. Each "py_*" function wraps the
 * "*" C function.
 */

/*void gc_sound_play_ogg_list( GList* files ); */
static PyObject*
py_gc_sound_play_ogg_list(PyObject* self, PyObject* args)
{
  GList* list;
  PyObject* pylist;
  /* Parse arguments */
  if(!PyArg_ParseTuple(args, "O:gc_sound_play_ogg_list", &pylist))
    return NULL;
  list = (GList*) pygobject_get(pylist);

  /* Call the corresponding C function */
  gc_sound_play_ogg_list(list);

  /* Create and return the result */
  Py_INCREF(Py_None);
  return Py_None;
}



/* void gc_sound_play_ogg(char *, ...);
   The method: gc_sound_play_ogg_list( GList* ) is used
   to perform the core call. (Because there's no way to construct
   a variable argument function call.
*/

static PyObject*
py_gc_sound_play_ogg(PyObject* self, PyObject* args)
{
  PyObject* item;
  GList* list = NULL;
  int i, length;

  /* Parse arguments */
  length = PyTuple_Size(args);
  if(length<1) return NULL;
  for(i=0; i<length; i++){
    item = PyTuple_GetItem(args, i);
    list = g_list_append(list, PyString_AsString(item));
  }

  /* Call the corresponding C function */
  gc_sound_play_ogg_list(list);
  g_list_free(list);

  /* Create and return the result */
  Py_INCREF(Py_None);
  return Py_None;
}



static PyObject*
py_gc_sound_reopen(PyObject* self, PyObject* args)
{
  /* Parse arguments */
  if(!PyArg_ParseTuple(args, ":gcompris.reopen_sound"))
    return NULL;

  /* Call the corresponding C function */
  gc_sound_reopen();

  /* Create and return the result */
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject*
py_gc_sound_close(PyObject* self, PyObject* args)
{
  /* Parse arguments */
  if(!PyArg_ParseTuple(args, ":gcompris.close_sound"))
    return NULL;

  /* Call the corresponding C function */
  gc_sound_close();

  /* Create and return the result */
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject*
py_gc_sound_pause(PyObject* self, PyObject* args)
{
  /* Parse arguments */
  if(!PyArg_ParseTuple(args, ":gcompris.pause_sound"))
    return NULL;

  /* Call the corresponding C function */
  gc_sound_pause();

  /* Create and return the result */
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject*
py_gc_sound_resume(PyObject* self, PyObject* args)
{
  /* Parse arguments */
  if(!PyArg_ParseTuple(args, ":gcompris.sound.resume"))
    return NULL;

  /* Call the corresponding C function */
  gc_sound_resume();

  /* Create and return the result */
  Py_INCREF(Py_None);
  return Py_None;
}

/********************************************/
/* sound callback                           */
static GHashTable *py_sound_callbacks=NULL;

void pyGcomprisSoundCallback(gchar *file){
  PyObject* result;
  PyObject* py_cb;

  g_warning("python sound callback : %s", file);

  PyGILState_STATE gil;

  g_assert ( py_sound_callbacks != NULL);

  py_cb = g_hash_table_lookup(py_sound_callbacks, file);

  //g_hash_table_remove(py_sound_callbacks, file);

  if(py_cb==NULL) return;

  if (!Py_IsInitialized())
    return;

  gil = pyg_gil_state_ensure();

  result = PyObject_CallFunction(py_cb, "O", PyString_FromString(file));

  // This callback can be called multiple time ?

  Py_DECREF(py_cb);

  if(result==NULL){
    PyErr_Print();
  } else {
    Py_DECREF(result);
  }

  pyg_gil_state_release(gil);

}


/* void gc_sound_policy_set(guint); */
static PyObject*
py_gc_sound_policy_set(PyObject* self, PyObject* args)
{
  GcSoundPolicy policy;
  PyObject *py_policy = NULL;

  /* Parse arguments */
  if(!PyArg_ParseTuple(args, "O:gc_sound_policy_set",&py_policy))
    return NULL;

  if (pyg_enum_get_value(GC_TYPE_SOUND_POLICY, py_policy, (gpointer)&policy))
        return NULL;

  /* Call the corresponding C function */
  gc_sound_policy_set(policy);

  /* Create and return the result */
  Py_INCREF(Py_None);
  return Py_None;
}

/* int	 gc_sound_policy_get(void); */
static PyObject*
py_gc_sound_policy_get(PyObject* self, PyObject* args)
{
  GcSoundPolicy policy;

  /* Parse arguments */
  if(!PyArg_ParseTuple(args, ":gc_sound_policy_get"))
    return NULL;

  /* Call the corresponding C function */
  policy = gc_sound_policy_get();
    
  return pyg_enum_from_gtype(GC_TYPE_SOUND_POLICY, policy);
}


static PyMethodDef PythonGcomprisSoundModule[] = {
  { "play_ogg_list",  py_gc_sound_play_ogg_list, METH_VARARGS, "gc_sound_play_ogg_list" },
  { "play_ogg",  py_gc_sound_play_ogg, METH_VARARGS, "gc_sound_play_ogg" },
  { "reopen",  py_gc_sound_reopen, METH_VARARGS, "gc_sound_reopen" },
  { "close",  py_gc_sound_close, METH_VARARGS, "gc_sound_close" },
  { "pause",  py_gc_sound_pause, METH_VARARGS, "gc_sound_pause" },
  { "resume",  py_gc_sound_resume, METH_VARARGS, "gc_sound_resume" },
  { "policy_get",  py_gc_sound_policy_get, METH_VARARGS, "gc_sound_policy_get" },
  { "policy_set",  py_gc_sound_policy_set, METH_VARARGS, "gc_sound_policy_set" },
  { NULL, NULL, 0, NULL}
};

void python_gcompris_sound_module_init(void)
{
  PyObject* module;
  module = Py_InitModule("_gcompris_sound", PythonGcomprisSoundModule);
}

/* Some usefull code parts ... */
/*
static PyObject*
py_gcompris_(PyObject* self, PyObject* args)
{
*/  /* Parse arguments */
/*  if(!PyArg_ParseTuple(args, ":gcompris_"))
    return NULL;
*/
  /* Call the corresponding C function */
/*  gcompris_();
*/
  /* Create and return the result */
/*  Py_INCREF(Py_None);
  return Py_None;
}
*/
/*
  { "",  py_gcompris_, METH_VARARGS, "gcompris_" },
*/
