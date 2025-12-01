const KEY = 'appointments';


export function getItem(){
try{
const raw = localStorage.getItem(KEY);
return raw ? JSON.parse(raw) : [];
}catch(e){
console.error('getItem parse error', e);
return [];
}
}


export function setItem(arr){
try{
localStorage.setItem(KEY, JSON.stringify(arr));
}catch(e){
console.error('setItem error', e);
}
}


export function removeItemById(id){
const items = getItem();
const filtered = items.filter(i => i.id !== id);
setItem(filtered);
}


export function clearAll(){
localStorage.removeItem(KEY);
}