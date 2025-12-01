import { getItem, removeItemById } from './storageUtils.js';


const listContainer = document.getElementById('listContainer');
const search = document.getElementById('search');


function renderList(items){
if(!items.length){
listContainer.innerHTML = '<p>No records available.</p>';
